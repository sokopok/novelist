from __future__ import annotations
from typing import Tuple, Literal, Annotated, Union, List, Dict, Optional, Any
from pydantic import BaseModel, Field
from pydantic.config import ConfigDict
from fastapi import FastAPI, HTTPException
from fastapi.responses import FileResponse
from fastapi.middleware.cors import CORSMiddleware
# from openai import OpenAI
import sqlite3, datetime, json, os
import networkx as nx



# TODO: hydrate needs to check project



app = FastAPI(title='Novelist HTTP')
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:5173", "http://localhost:3000"],  # your frontend
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)



# aiclient = OpenAI(api_key=settings.OPENAI_API_KEY)

# def ai_generate_response(input: Union[str,List[str],List[Dict[str,Any]]], model:str='', instructions:str='', previous_response_id:str=''):
#     return aiclient.responses.create(
#         model=model or None,
#         instructions=instructions or None,
#         input=input or None,
#         previous_response_id=previous_response_id or None,
#     )



class StoryGraphError(RuntimeError):
    """
    Base exception for all story-graph related errors.

    Raised when an invalid operation is attempted on the story graph,
    such as using an unknown edge kind or an invalid node/edge identifier.
    """

    base: Optional[Exception]

    def __init__(self, msg: str = "", base: Optional[Exception] = None) -> None:
        """
        Initialize a new DatabaseError.

        Args:
            msg: Human-readable description of the error.
            base: Optional underlying exception that triggered this error.
        """
        super().__init__(msg)
        self.base = base

class StoryGraphOperationError(StoryGraphError):
    """
    Exception raised when a story-graph operation cannot be applied.

    Used specifically for failures in structured `StoryGraphOperation` batches,
    e.g. invalid nodes/edges, conflicting updates, or constraint violations.
    """
    pass



class DatabaseError(RuntimeError):
    """
    High-level error raised for database-related failures.

    This wraps lower-level exceptions from SQLite and preserves the original
    exception instance in ``base`` so callers can inspect the root cause.
    """

    base: Optional[Exception]

    def __init__(self, msg: str = "", base: Optional[Exception] = None) -> None:
        """
        Initialize a new DatabaseError.

        Args:
            msg: Human-readable description of the error.
            base: Optional underlying exception that triggered this error.
        """
        super().__init__(msg)
        self.base = base

class Database:
    """
    Lightweight wrapper around an SQLite connection for story persistence.

    Responsibilities:
    - Open and manage a single SQLite connection.
    - Provide transaction helpers (commit/rollback + *and_close variants).
    - Persist time-stamped JSON snapshots of nodes, edges, and operations.

    Schema assumptions (must exist in the database):
        nodes(t TEXT, id TEXT, json TEXT)
        edges(t TEXT, id TEXT, json TEXT)
        operations(t TEXT, json TEXT)

    The objects passed to `insert_*` / `update_*` methods are expected to be
    Pydantic models (or compatible objects) that implement ``model_dump()``.
    """

    #: Path to the SQLite database file this instance is connected to.
    filename: str

    #: Underlying SQLite connection; set in ``__init__`` and cleared on close.
    connection: Optional[sqlite3.Connection]

    def __init__(self, filename: str) -> None:
        """
        Open a new SQLite connection to the given file.

        Args:
            filename: Path to the SQLite database file.

        Raises:
            DatabaseError: If ``filename`` is empty.
        """
        if not filename:
            raise DatabaseError("missing filename")

        self.filename = filename
        self.connection = sqlite3.connect(self.filename)

    # --------------------------------------------------------------------- #
    # Transaction helpers
    # --------------------------------------------------------------------- #

    def commit(self) -> None:
        """
        Commit the current transaction.

        If the commit fails, a rollback is attempted and a DatabaseError is
        raised with the original exception attached in ``base``.
        """
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.commit()
        except Exception as exc:  # noqa: BLE001
            self.rollback()
            raise DatabaseError("commit failed", exc) from exc

    def commit_and_close(self) -> None:
        """
        Commit the current transaction and close the connection.

        If the commit fails, a rollback is attempted and a DatabaseError is
        raised. The connection is always closed in a ``finally`` block.
        """
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.commit()
        except Exception as exc:  # noqa: BLE001
            self.rollback()
            raise DatabaseError("commit_and_close failed", exc) from exc
        finally:
            self.connection.close()
            self.connection = None

    def rollback(self) -> None:
        """
        Roll back the current transaction, if the connection is open.

        This is a no-op if the connection has already been closed or was never
        successfully established.
        """
        if not self.connection:
            return

        self.connection.rollback()

    def rollback_and_close(self) -> None:
        """
        Roll back the current transaction (if any) and close the connection.

        The connection is cleared from the instance after closing.
        """
        if not self.connection:
            return

        try:
            self.connection.rollback()
        finally:
            self.connection.close()
            self.connection = None

    # --------------------------------------------------------------------- #
    # Low-level helpers
    # --------------------------------------------------------------------- #

    @staticmethod
    def timestamp() -> str:
        """
        Return the current time as an ISO 8601 string.

        This timestamp is stored alongside each JSON snapshot to make the
        history of changes easy to reconstruct.
        """
        return datetime.datetime.now().isoformat()

    def insert_node_kind(self, key: str, data: Dict[str,Any]) -> None:
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute(
                "INSERT INTO nodekinds (ts, k, d) VALUES (?,?,?)",
                (self.timestamp(), key, json.dumps(data)),
            )
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"insert_node: {exc}", exc) from exc

    def replace_node_kind(self, key: str, data: Dict[str,Any]) -> None:
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute(
                "REPLACE INTO nodekinds (ts, k, d) VALUES (?,?,?)",
                (self.timestamp(), key, json.dumps(data)),
            )
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"insert_node: {exc}", exc) from exc

    def delete_node_kind(self, key: str) -> None:
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute("DELETE FROM nodekinds WHERE k=?", (key,))
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"delete_node: {exc}", exc) from exc

    def insert_edge_kind(self, key: str, data: Dict[str,Any]) -> None:
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute(
                "INSERT INTO edgekinds (ts, k, d) VALUES (?,?,?)",
                (self.timestamp(), key, json.dumps(data)),
            )
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"insert_node: {exc}", exc) from exc

    def replace_edge_kind(self, key: str, data: Dict[str,Any]) -> None:
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute(
                "REPLACE INTO edgekinds (ts, k, d) VALUES (?,?,?)",
                (self.timestamp(), key, json.dumps(data)),
            )
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"insert_node: {exc}", exc) from exc

    def delete_edge_kind(self, key: str) -> None:
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute("DELETE FROM edgekinds WHERE k=?", (key,))
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"delete_node: {exc}", exc) from exc

    def insert_affect(self, key: str, data: Dict[str,Any]) -> None:
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute(
                "INSERT INTO affects (ts, k, d) VALUES (?,?,?)",
                (self.timestamp(), key, json.dumps(data)),
            )
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"insert_affect: {exc}", exc) from exc

    def replace_affect(self, key: str, data: Dict[str,Any]) -> None:
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute(
                "REPLACE INTO affects (ts, k, d) VALUES (?,?,?)",
                (self.timestamp(), key, json.dumps(data)),
            )
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"insert_node: {exc}", exc) from exc

    def delete_affect(self, key: str) -> None:
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute("DELETE FROM affects WHERE k=?", (key,))
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"delete_node: {exc}", exc) from exc

    # --------------------------------------------------------------------- #
    # Node persistence
    # --------------------------------------------------------------------- #

    def insert_node(self, key: str, kind: str, data: Dict[str,Any]) -> None:
        """
        Insert a new node snapshot into the ``nodes`` table.

        Args:
            node: Node object to persist. Must expose an ``id`` attribute and
                  implement ``model_dump()`` returning a JSON-serializable dict.

        Raises:
            DatabaseError: If the INSERT fails for any reason.
        """
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute(
                "INSERT INTO nodes (ts, id, k, d) VALUES (?,?,?,?)",
                (self.timestamp(), key, kind, json.dumps(data)),
            )
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"insert_node: {exc}", exc) from exc

    def replace_node(self, node_id: str, updated: Any) -> None:
        """
        Insert or replace a node snapshot in the ``nodes`` table.

        Uses ``REPLACE`` to maintain the latest state keyed by ``id`` while
        still storing a timestamp for each update.

        Args:
            node_id: Identifier of the node being updated.
            updated: Updated node object implementing ``model_dump()``.

        Raises:
            DatabaseError: If the REPLACE fails.
        """
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            json_data = json.dumps(updated.model_dump())
            self.connection.execute(
                "REPLACE INTO nodes (t, id, json) VALUES (?, ?, ?)",
                (self.timestamp(), node_id, json_data),
            )
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"update_node: {exc}", exc) from exc

    def delete_node(self, node_id: str) -> None:
        """
        Delete a node from the ``nodes`` table.

        Args:
            node_id: Identifier of the node to delete.

        Raises:
            DatabaseError: If the DELETE fails.
        """
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute("DELETE FROM nodes WHERE id = ?", (node_id,))
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"delete_node: {exc}", exc) from exc

    # --------------------------------------------------------------------- #
    # Edge persistence
    # --------------------------------------------------------------------- #

    def insert_edge(self, source: str, target: str, key: int, kind: str, data: Dict[str,Any]) -> None:
        """
        Insert a new edge snapshot into the ``edges`` table.

        Args:
            edge: Edge object to persist. Must expose an ``id`` attribute and
                  implement ``model_dump()`` returning a JSON-serializable dict.

        Raises:
            DatabaseError: If the INSERT fails.
        """
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute(
                "INSERT INTO edges (t,s,t,i,k,json) VALUES (?,?,?,?,?,?)",
                (self.timestamp(), source, target, key, kind, json.dumps(data)),
            )
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"insert_edge: {exc}", exc) from exc

    def replace_edge(self, source: str, target: str, key: int, kind: str, data: Dict[str,Any]) -> None:
        """
        Insert a new edge snapshot into the ``edges`` table.

        Args:
            edge: Edge object to persist. Must expose an ``id`` attribute and
                  implement ``model_dump()`` returning a JSON-serializable dict.

        Raises:
            DatabaseError: If the INSERT fails.
        """
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            self.connection.execute(
                "REPLACE INTO edges (ts,s,t,i,k,d) VALUES (?,?,?,?,?,?)",
                (self.timestamp(), source, target, key, kind, json.dumps(data)),
            )
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"insert_edge: {exc}", exc) from exc

    def delete_edge(self, source: str='', target: str='', key: int=-1, kind: str='') -> None:
        """
        Delete an edge from the ``edges`` table.

        Args:
            edge_id: Identifier of the edge to delete.

        Raises:
            DatabaseError: If the DELETE fails.
        """
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            if source == '' and target == '' and key < 0 and kind == '':
                self.connection.execute(
                    "DELETE FROM edges"
                )
            elif target == '' and key < 0 and kind == '':
                self.connection.execute(
                    "DELETE FROM edges WHERE s=?",
                    (source,)
                )
            elif source == '' and key < 0 and kind == '':
                self.connection.execute(
                    "DELETE FROM edges WHERE t=?",
                    (target,)
                )
            elif source == '' and target == '' and kind == '':
                self.connection.execute(
                    "DELETE FROM edges WHERE i=?",
                    (key,)
                )
            elif source == '' and target == '' and key < 0:
                self.connection.execute(
                    "DELETE FROM edges WHERE k=?",
                    (kind,)
                )
            elif source == '' and target == '':
                self.connection.execute(
                    "DELETE FROM edges WHERE i=? AND k=?",
                    (key, kind)
                )
            elif source == '':
                self.connection.execute(
                    "DELETE FROM edges WHERE t=? AND i=? AND k=?",
                    (target, key, kind)
                )
            elif target == '':
                self.connection.execute(
                    "DELETE FROM edges WHERE s=? AND i=? AND k=?",
                    (source, key, kind)
                )
            elif kind == '':
                self.connection.execute(
                    "DELETE FROM edges WHERE s=? AND t=? AND i=?",
                    (source, target, key)
                )
            elif key == -1 and kind == '':
                self.connection.execute(
                    "DELETE FROM edges WHERE s=? AND t=?",
                    (source, target)
                )
            elif key == -1:
                self.connection.execute(
                    "DELETE FROM edges WHERE s=? AND t=? AND k=?",
                    (source, target, kind)
                )
            elif kind == '':
                self.connection.execute(
                    "DELETE FROM edges WHERE s=? AND t=? AND i=?",
                    (source, target, key)
                )
            else:
                self.connection.execute(
                    "DELETE FROM edges WHERE s=? AND t=? AND i=? AND k=?",
                    (source, target, key, kind)
                )
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"delete_edge: {exc}", exc) from exc

    # --------------------------------------------------------------------- #
    # Operation persistence
    # --------------------------------------------------------------------- #

    def insert_operation(self, operation: Any) -> None:
        """
        Record a story-graph operation in the ``operations`` table.

        The full operation payload is stored as JSON, together with a
        timestamp. ``operation`` is typically a Pydantic model representing a
        `StoryGraphOperation`, but any object with ``model_dump()`` is accepted.

        Args:
            operation: Operation object to persist.

        Raises:
            DatabaseError: If the INSERT fails.
        """
        if not self.connection:
            raise DatabaseError("connection is not initialized")

        try:
            json_data = json.dumps(operation.model_dump())
            self.connection.execute(
                "INSERT INTO operations (t, json) VALUES (?, ?)",
                (self.timestamp(), json_data),
            )
        except Exception as exc:  # noqa: BLE001
            raise DatabaseError(f"insert_operation: {exc}", exc) from exc




class AffectDefinition(BaseModel):
    """
    Schema describing a single affect dimension.

    An `AffectDefinition` explains what an affect key means in narrative or
    simulation terms. Instances are stored in the global
    `AFFECTDEFS` registry and referenced by their `key`.
    """

    key: str = Field(
        ...,
        description=(),
    )

    label: str = Field(
        ...,
        description=(
            "Short human-readable label for this affect (e.g. 'Intensity', "
            "'Satiation'). Suitable for UI display."
        ),
    )

    description: str = Field(
        "",
        description=(
            "Full textual description of what this affect represents, how it "
            "should be interpreted, and how it typically influences behaviour."
        ),
    )

    def model_post_init(self, __context) -> None:
        """
        Post-initialization hook to enforce invariants and derive fields.

        - Ensures that `key` is not empty; raises `ValueError('key')` if it is.
        - If `id` is empty, derives it as 'affect:{key}' to ensure a stable,
          namespaced identifier.
        """
        super().model_post_init(__context)

        if not self.key:
            raise ValueError("key")

    def dump(self):
        return self.model_dump(exclude_unset=True, exclude_none=True)

class Affect(BaseModel):
    """
    A single scalar affect dimension for an entity.

    An `Affect` instance ties an affect definition (by `affect_key`) to a
    numeric value and optional explanatory notes. The key is resolved against
    the global `AFFECTDEFS` registry.
    """

    key: str = Field(
        ...,
        description=(
            "Key referencing an `AffectDefinition` in the global "
            "`AFFECTDEFS` registry (e.g. 'motivation.intensity')."
        ),
    )

    value: float = Field(
        0.0,
        description=(
            "Numeric value for this affect dimension. The exact scale is "
            "configuration-dependent, but is typically within a bounded range "
            "such as [0.0, 1.0] or [-1.0, 1.0]."
        ),
    )

    notes: List[str] = Field(
        default_factory=list,
        description=(
            "Optional free-form notes describing how or why this value was set "
            "or adjusted (e.g. references to events, design comments)."
        ),
    )

    @property
    def affect(self) -> Optional[AffectDefinition]:
        """
        Resolve this affect's definition from the global registry.

        Returns:
            The corresponding `AffectDefinition` for `self.affect_key` in `AFFECTDEFS`.
        """
        return AFFECTDEFS[self.key]

    def dump(self):
        return self.model_dump(exclude_unset=True, exclude_none=True)

class AffectData(BaseModel):
    """
    Container for the affect state of an entity.

    `baseline` captures stable or long-term tendencies (how the entity feels or
    behaves in a neutral context), while `current` tracks the moment-to-moment
    values that may be influenced by events, interactions, and simulation rules.
    """

    baseline: Dict[str, Affect] = Field(
        default_factory=dict,
        description=(
            "Baseline affect values for this entity, keyed by affect key "
            "(e.g. 'motivation.intensity'). These represent long-term or "
            "default tendencies the system can drift back toward over time."
        ),
    )
    current: Dict[str, Affect] = Field(
        default_factory=dict,
        description=(
            "Current affect values for this entity, keyed by affect key. "
            "These are the live values updated by events and simulation, "
            "and may temporarily diverge from the baseline."
        ),
    )

AFFECTDEFS: Dict[str, AffectDefinition] = {
    "motivation.intensity": AffectDefinition(
        key="motivation.intensity",
        label="Intensity",
        description="How strongly this motivation is pushing right now.",
    ),
    "motivation.satiation": AffectDefinition(
        key="motivation.satiation",
        label="Satiation",
        description="How fulfilled or satisfied this motivation currently feels.",
    ),
    "motivation.importance": AffectDefinition(
        key="motivation.importance",
        label="Importance",
        description="How important or central this motivation is to the agent.",
    ),
}



class AffectTransport(BaseModel):
    key: str = Field(...)
    value: float= Field(...)
    notes: Optional[List[str]] = Field(None)

    @property
    def extra(self):
        return self.__pydantic_extra__ or {}

    model_config = ConfigDict(extra='allow', arbitrary_types_allowed=True)

    @staticmethod
    def hydrate(data: dict):
        """
        Convert a generic node payload into a concrete Node subclass instance.

        The function inspects the `type` field of the payload and uses the `NODE_TYPES`
        map to choose the correct Pydantic model (e.g. Story, Scene, Character).
        It then validates and constructs that model via `model_validate`.

        :param data: Raw node dict containing at least a `type` field.
        :return: A fully validated Node (Story/Scene/Character/etc.).
        :raises ValueError: If `type` is missing or not registered in `NODE_TYPES`.
        """
        return model_validate(data)

    def dump(self):
        return self.model_dump(exclude_unset=True, exclude_none=True)

class AffectDefinitionTransport(BaseModel):
    key: str = Field(...)

    label: str = Field(
        ...,
        description=(
            "Short human-readable label for this affect (e.g. 'Intensity', "
            "'Satiation'). Suitable for UI display."
        ),
    )

    description: str = Field(
        "",
        description=(
            "Full textual description of what this affect represents, how it "
            "should be interpreted, and how it typically influences behaviour."
        ),
    )

    @property
    def extra(self):
        return self.__pydantic_extra__ or {}

    model_config = ConfigDict(extra='allow', arbitrary_types_allowed=True)

    @staticmethod
    def hydrate(data: dict):
        """
        Convert a generic node payload into a concrete Node subclass instance.

        The function inspects the `type` field of the payload and uses the `NODE_TYPES`
        map to choose the correct Pydantic model (e.g. Story, Scene, Character).
        It then validates and constructs that model via `model_validate`.

        :param data: Raw node dict containing at least a `type` field.
        :return: A fully validated Node (Story/Scene/Character/etc.).
        :raises ValueError: If `type` is missing or not registered in `NODE_TYPES`.
        """
        return model_validate(data)

    def dump(self):
        return self.model_dump(exclude_unset=True, exclude_none=True)

class NodeUi(BaseModel):
    id: str = Field(...)
    kind: str = Field('node')
    label: str = Field(id)
    x: float = Field(0.0)
    y: float = Field(0.0)
    z: float = Field(0.0)
    data: Dict[str,Any] = Field(default_factory=dict)

class EdgeUi(BaseModel):
    id: str = Field('')
    kind: str = Field(...)
    source: str = Field(...)
    target: str = Field(...)
    key: int = -1
    label: str = Field('')
    weight: float = Field(1.0)
    data: Dict[str,Any] = Field(default_factory=dict)

    def model_post_init(self, __context: Any) -> None:
        super().model_post_init(__context)

        if not self.id:
            self.id = f'{self.source} {self.kind}.{self.key} {self.target}'
        if not self.label:
            self.label = self.id

class GraphUi(BaseModel):
    nodes: List[NodeUi]
    edges: List[EdgeUi]

class NodeTransport(BaseModel):
    key: str = Field(..., description="Human-readable, short key that uniquely identifies this node within its type. Used to derive the `id`.")
    kind: str = Field(..., description="Node kind. Used to derive the `id`.")
    category: Literal['', 'narrative', 'focus', 'event'] = Field('')
    status: Optional[Literal["experimental", "draft", "active", "archived", "final"]] = Field(None,
        description=(
            "Lifecycle status of this node:\n"
            "- `experimental`: highly unstable, used for exploration.\n"
            "- `draft`: under active development and subject to change.\n"
            "- `active`: currently in use in the story simulation.\n"
            "- `archived`: no longer actively used but preserved for history.\n"
            "- `final`: considered stable and not expected to change."
        ),
    )

    affect: Optional[AffectData] = Field(None)

    edges: Optional[Dict[str, Dict[str, Any]]] = Field(None)

    ui: Optional[NodeUi] = Field(None)

    @property
    def extra(self):
        return self.__pydantic_extra__ or {}

    model_config = ConfigDict(extra='allow', arbitrary_types_allowed=True)

    @staticmethod
    def hydrate(data: dict):
        """
        Convert a generic node payload into a concrete Node subclass instance.

        The function inspects the `type` field of the payload and uses the `NODE_TYPES`
        map to choose the correct Pydantic model (e.g. Story, Scene, Character).
        It then validates and constructs that model via `model_validate`.

        :param data: Raw node dict containing at least a `type` field.
        :return: A fully validated Node (Story/Scene/Character/etc.).
        :raises ValueError: If `type` is missing or not registered in `NODE_TYPES`.
        """
        node_kind = data.get("kind")
        if not node_kind:
            raise ValueError("node.kind is required")
        if node_kind not in NODEKINDS:
            raise ValueError(f"invalid node.kind: {node_kind}")

        transport_class = NODEKINDS[node_kind].transport_class
        if not transport_class:
            raise ValueError(f"no transport_class for node_kind: {node_kind}")

        return transport_class.model_validate(data)

    def model_post_init(self, __context: Any) -> None:
        super().model_post_init(__context)

        kind = NODEKINDS.get(self.kind)
        if kind and kind.affective and not self.affect:
            self.affect = AffectData()

    def dump(self):
        return self.model_dump(exclude_unset=True, exclude_none=True)

class NarrativeNodeTransport(NodeTransport):
    category: Literal['narrative'] = 'narrative'
    title: Optional[str] = Field(None)
    subtitle: Optional[str] = Field(None)
    summary: Optional[str] = Field(None)

class StoryTransport(NarrativeNodeTransport):
    pass

class SceneTransport(NarrativeNodeTransport):
    pass

class BeatTransport(NarrativeNodeTransport):
    pass

class FocusNodeTransport(NodeTransport):
    category: Literal['focus'] = 'focus'
    name: Optional[str] = Field(None)
    role: Optional[str] = Field(None)
    summary: Optional[str] = Field(None)

class CharacterTransport(FocusNodeTransport):
    who: Optional[str] = Field(None)

class PlaceTransport(FocusNodeTransport):
    where: Optional[str] = Field(None)

class ThingTransport(FocusNodeTransport):
    what: Optional[str] = Field(None)

class MotivationTransport(FocusNodeTransport):
    why: Optional[str] = Field(None)

class ArcTransport(NodeTransport):
    truth: Optional[str] = Field(None)
    lie: Optional[str] = Field(None)

class ArcStageTransport(NodeTransport):
    range_min: Optional[float] = Field(None)
    range_max: Optional[float] = Field(None)
    description: Optional[str] = Field(None)
    stage: Optional[str] = Field(None)

class EdgeTransport(BaseModel):
    key: str = Field('', description="Human-readable, short key that uniquely identifies this edge within its type. Used to derive the `id`.")

    source: str = Field(
        ...,
        description=(
            "Identifier of the source node from which this edge originates. "
            "The node is looked up in the attached `StoryGraph`."
        ),
    )
    source_kind: str = Field(
        ''
    )

    target: str = Field(
        ...,
        description=(
            "Identifier of the target node to which this edge points. "
            "The node is looked up in the attached `StoryGraph`."
        ),
    )
    target_kind: str = Field(
        ''
    )

    kind: str = Field(..., description="Edge kind. Used to derive the `id`.")

    status: Optional[Literal["experimental", "draft", "active", "archived", "final"]] = Field(None,
        description=(
            "Lifecycle status of this edge:\n"
            "- `experimental`: highly unstable, used for exploration.\n"
            "- `draft`: under active development and subject to change.\n"
            "- `active`: currently in use in the story simulation.\n"
            "- `archived`: no longer actively used but preserved for history.\n"
            "- `final`: considered stable and not expected to change."
        ),
    )

    @property
    def extra(self):
        return self.__pydantic_extra__ or {}

    model_config = ConfigDict(extra='allow', arbitrary_types_allowed=True)

    @staticmethod
    def hydrate(data: dict):
        """
        Convert a generic edge payload into a concrete EdgeTransport subclass instance.
        """
        edge_kind = data.get("kind")
        if not edge_kind:
            raise ValueError("edge.kind is required")
        if edge_kind not in EDGEKINDS:
            raise ValueError(f"invalid edge.kind: {edge_kind}")
        transport_class = EDGEKINDS[edge_kind].transport_class
        if not transport_class:
            raise ValueError(f"no transport_class for edge_kind: {edge_kind}")
        return transport_class.model_validate(data)

    def dump(self):
        return self.model_dump(exclude_unset=True, exclude_none=True)

class RelatedToEdgeTransport(EdgeTransport):
    role: Optional[str] = Field(None)
    affect: Optional[AffectData] = Field(None)

class NodeKindTransport(BaseModel):
    key: str = Field(...)
    label: Optional[str] = Field(None)
    title: Optional[str] = Field(None)
    description: Optional[str] = Field(None)
    category: Optional[str] = Field(None)
    allowed_connections: Optional[Dict[str, List[str]]] = Field(None)
    transport_class: Optional[str] = Field(None)

    @staticmethod
    def hydrate(data: dict):
        key = data.get("key")
        if not key:
            raise StoryGraphError('key is required')
        if 'label' not in data:
            data['label'] = key
        if 'title' not in data:
            data['title'] = data['label']
        if 'category' not in data:
            data['category'] = 'default'
        if 'transport_class' not in data:
            data['transport_class'] = 'NodeTransport'
        return NodeKindTransport.model_validate(data)

class EdgeKindTransport(BaseModel):
    key: str = Field(...)
    label: Optional[str] = Field(None)
    title: Optional[str] = Field(None)
    description: Optional[str] = Field(None)
    category: Optional[str] = Field(None)
    directed: bool = Field(True)
    transitive: bool = Field(False)
    acyclic: bool = Field(True)
    multiple_allowed: bool = Field(False)
    reverse: Optional[str] = Field(None)
    allowed_connections: Optional[Dict[str, List[str]]] = Field(None)
    score_hint: Optional[str] = Field(None)
    transport_class: Optional[str] = Field(None)

    @staticmethod
    def hydrate(data: dict):
        key = data.get("key")
        if not key:
            raise StoryGraphError('key is required')
        if 'label' not in data:
            data['label'] = key
        if 'title' not in data:
            data['title'] = data['label']
        if 'category' not in data:
            data['category'] = 'default'
        if 'transport_class' not in data:
            data['transport_class'] = 'EdgeTransport'
        return EdgeKindTransport.model_validate(data)



class Operation(BaseModel):
    operation: Literal[
        "node.add",
        "node.update",
        "node.delete",
        "edge.add",
        "edge.update",
        "edge.delete",
        "nodekind.add",
        "nodekind.update",
        "nodekind.delete",
        "edgekind.add",
        "edgekind.update",
        "edgekind.delete",
        "affectdef.add",
        "affectdef.update",
        "affectdef.delete",
    ] = Field(...)

    notes: List[str] = Field(
        default_factory=list,
        description=(
            "Optional free-form notes or commentary about this operation. "
            "Useful for audit trails, debugging, or human-readable context."
        ),
    )

    dry_run: bool = Field(
        False,
        description=(
            "If True, the operation should be validated and simulated only, "
            "without actually mutating the graph or database."
        ),
    )

    def execute(
        self,
        graph: Union['StoryGraph',None]=None,
        database: Database|None=None,
        auto_commit: bool=True,
    ):
        pass

    def dump(self):
        return self.model_dump(exclude_unset=True, exclude_none=True)

class Operations(Operation):
    operations: List[Operation] = Field(
        default_factory=list,
        description="Ordered list of story-graph operations to apply as a single batch.",
    )

    def execute(self, database: Database|None=None, auto_commit: bool=True):
        try:
            for operation in self.operations:
                operation.execute(database)
            if auto_commit:
                self.commit()

        except Exception as e:
            self.rollback()
            raise StoryGraphError('execute', base=e)

    def commit(self):
        pass

    def rollback(self):
        pass

    def dump(self):
        return self.model_dump(exclude_unset=True, exclude_none=True)

class MutationProposal(BaseModel):
    """A structured proposal for extending or modifying the story definition or schema."""

    id: str = Field(..., description="Stable identifier for this proposal.")
    timestamp: str = Field(..., description="ISO8601 timestamp when the proposal was created.")

    status: Literal[
        "proposed",
        "accepted",
        "rejected",
        "deprecated",
        "implemented"
    ] = Field("proposed", description="Lifecycle state of this mutation proposal.")

    description: str = Field(
        ...,
        description="Plain-language explanation of what this mutation does."
    )

    rationale: str = Field(
        ...,
        description="Concise justification for why this change improves the story model."
    )

    impact_analysis: Optional[str] = Field(
        None,
        description="Anticipated effects on simulation, schema, or existing data."
    )

    constraints: Optional[Dict[str, Any]] = Field(
        None,
        description="New validation rules, ranges, enums, or invariants introduced."
    )

    reviewer_notes: Optional[str] = Field(
        None,
        description="Space for human review decisions or commentary."
    )

    operations: List[Operation] = Field(default_factory=list)




class AffectDefinitionOperation(Operation):
    operation: Literal[
        "affectdef.add",
        "affectdef.update",
        "affectdef.delete",
    ] = Field(...)

class AddAffectDefinitionOperation(AffectDefinitionOperation):
    operation: Literal["affectdef.add"] = Field("affectdef.add")
    data: dict = Field(...)

    def execute(
        self,
        graph: Union['StoryGraph',None]=None,
        database: Database|None=None,
        auto_commit: bool=True,
    ):
        key = self.data.get('key')
        if not key:
            raise StoryGraphError('key is required')
        if key in AFFECTDEFS:
            raise StoryGraphError(f'duplicate key: "{key}"')

        hydrated = AffectDefinitionTransport.hydrate(self.data)
        if not hydrated:
            raise StoryGraphError(f'invalid data: "{self.data}"')

        affectdef = AffectDefinition(
            key=hydrated.key,
            label=hydrated.label,
            description=hydrated.description,
        )
        AFFECTDEFS[key] = affectdef

        if database:
            database.replace_affectdef(key, affectdef.dump())
            if auto_commit:
                database.commit()

class UpdateAffectDefinitionOperation(AffectDefinitionOperation):
    operation: Literal["affectdef.update"] = Field("affectdef.update")
    data: dict = Field(...)

    def execute(self, graph: 'StoryGraph', database: Database|None=None, auto_commit: bool=True):
        key = self.data.get('key')
        if not key:
            raise StoryGraphError('key is required')

        if key not in AFFECTDEFS:
            raise StoryGraphError(f'not found: "{key}"')

        hydrated = AffectDefinitionTransport.hydrate(self.data)
        if not hydrated:
            raise StoryGraphError(f'invalid data: "{self.data}"')

        affectdef = AFFECTDEFS[key]
        updated = affectdef.model_copy(update=hydrated, deep=True)
        AFFECTDEFS[key] = updated

        if database:
            database.replace_affectdef(key, updated.dump())
            if auto_commit:
                database.commit()

class DeleteAffectDefinitionOperation(AffectDefinitionOperation):
    operation: Literal["affectdef.delete"] = Field("affectdef.delete")
    key: str = Field(...)

    def execute(self, graph: 'StoryGraph', database: Database|None=None, auto_commit: bool=True):
        if not self.key:
            raise StoryGraphError('key is required')
        if key not in AFFECTDEFS:
            raise StoryGraphError(f'not found: "{key}"')

        del AFFECTDEFS[key]

        if database:
            database.delete_affectdef(key)
            if auto_commit:
                database.commit()

class NodeOperation(Operation):
    operation: Literal[
        "node.add",
        "node.update",
        "node.delete",
    ] = Field(...)

class AddNodeOperation(NodeOperation):
    operation: Literal["node.add"] = Field("node.add")
    data: dict = Field(...)

    def execute(
        self,
        graph: Union['StoryGraph',None]=None,
        database: Database|None=None,
        auto_commit: bool=True,
    ):
        if not graph:
            raise StoryGraphError('no graph')

        key = self.data.get('key')
        if not key:
            raise StoryGraphError('key is required')
        if graph.has_node(key):
            raise StoryGraphError(f'duplicate key: "{key}"')

        hydrated = NodeTransport.hydrate(self.data)
        if not hydrated:
            raise StoryGraphError(f'invalid data: "{self.data}"')

        graph.add_node(key, hydrated)

        if database:
            database.replace_node(key, hydrated.dump())
            if auto_commit:
                database.commit()

class UpdateNodeOperation(NodeOperation):
    operation: Literal["node.update"] = Field("node.update")
    data: dict = Field(...)

    def execute(self, graph: 'StoryGraph', database: Database|None=None, auto_commit: bool=True):
        if not graph:
            raise StoryGraphError('no graph')

        key = self.data.get('key')
        if not key:
            raise StoryGraphError('key is required')
        if not graph.has_node(key):
            raise StoryGraphError(f'not found: "{key}"')

        hydrated = NodeTransport.hydrate(self.data)
        if not hydrated:
            raise StoryGraphError(f'invalid data: "{self.data}"')

        graph.add_node(key, hydrated)

        if database:
            database.replace_node(key, hydrated.dump())
            if auto_commit:
                database.commit()

class DeleteNodeOperation(NodeOperation):
    operation: Literal["node.delete"] = Field("node.delete")
    key: str = Field(...)

    def execute(self, graph: 'StoryGraph', database: Database|None=None, auto_commit: bool=True):
        if not graph:
            raise StoryGraphError('no graph')

        if not self.key:
            raise StoryGraphError('key is required')
        if not graph.has_node(self.key):
            raise StoryGraphError(f'not found: "{key}"')

        graph.remove_node(key)

        if database:
            database.delete_node(key)
            if auto_commit:
                database.commit()

class EdgeOperation(Operation):
    operation: Literal[
        "edge.add",
        "edge.update",
        "edge.delete",
    ] = Field(...)

class AddEdgeOperation(EdgeOperation):
    operation: Literal["edge.add"] = Field("edge.add")
    source: str = Field(
        ...,
        description=(
            "Identifier of the source node from which this edge originates. "
            "The node is looked up in the attached `StoryGraph`."
        ),
    )
    target: str = Field(
        ...,
        description=(
            "Identifier of the target node to which this edge points. "
            "The node is looked up in the attached `StoryGraph`."
        ),
    )
    key: Optional[int] = Field(None)
    kind: Literal[
        "contains",
        "causes",
        "related_to",
    ] = Field(..., description="Edge kind. Used to derive the `id`.")
    data: dict = Field(...)

    def execute(
        self,
        graph: Union['StoryGraph',None]=None,
        database: Database|None=None,
        auto_commit: bool=True,
    ):
        if not graph:
            raise StoryGraphError('no graph')

        if not self.source:
            raise StoryGraphError('source is required')
        if not self.target:
            raise StoryGraphError('target is required')
        if not self.kind:
            raise StoryGraphError('kind is required')
        if self.kind not in EDGEKINDS:
            raise StoryGraphError(f'kind not found: {self.kind}')

        hydrated = EdgeTransport.hydrate(self.data)
        if not hydrated:
            raise StoryGraphError(f'invalid data: "{self.data}"')

        graph.add_edge(self.kind, self.source, self.target, self.key, hydrated)

        if database:
            database.replace_edge(self.source, self.target, self.key, self.kind, hydrated.dump())
            if auto_commit:
                database.commit()

class UpdateEdgeOperation(EdgeOperation):
    operation: Literal["edge.update"] = Field("edge.update")
    source: Optional[str] = Field(
        None,
        description=(
            "Identifier of the source node from which this edge originates. "
            "The node is looked up in the attached `StoryGraph`."
        ),
    )
    target: Optional[str] = Field(
        None,
        description=(
            "Identifier of the target node to which this edge points. "
            "The node is looked up in the attached `StoryGraph`."
        ),
    )
    key: Optional[int] = Field(None)
    kind: Optional[Literal[
        "contains",
        "causes",
        "related_to",
    ]] = Field(None, description="Edge kind. Used to derive the `id`.")
    data: dict = Field(...)

    def execute(self, graph: 'StoryGraph', database: Database|None=None, auto_commit: bool=True):
        if not graph:
            raise StoryGraphError('no graph')

        key = self.data.get('key')
        if not key:
            raise StoryGraphError('key is required')
        if not graph.has_edge(key):
            raise StoryGraphError(f'not found: "{key}"')

        hydrated = EdgeTransport.hydrate(self.data)
        if not hydrated:
            raise StoryGraphError(f'invalid data: "{self.data}"')

        graph.add_edge(key, hydrated)

        if database:
            database.replace_edge(key, hydrated.dump())
            if auto_commit:
                database.commit()

class DeleteEdgeOperation(EdgeOperation):
    operation: Literal["edge.delete"] = Field("edge.delete")
    source: Optional[str] = Field(
        None,
        description=(
            "Identifier of the source node from which this edge originates. "
            "The node is looked up in the attached `StoryGraph`."
        ),
    )
    target: Optional[str] = Field(
        None,
        description=(
            "Identifier of the target node to which this edge points. "
            "The node is looked up in the attached `StoryGraph`."
        ),
    )
    key: Optional[int] = Field(None)
    kind: Optional[Literal[
        "contains",
        "causes",
        "related_to",
    ]] = Field(None, description="Edge kind. Used to derive the `id`.")

    def execute(self, graph: 'StoryGraph', database: Database|None=None, auto_commit: bool=True):
        if not graph:
            raise StoryGraphError('no graph')

        graph.remove_edge(self.kind, self.source, self.target, self.key)

        if database:
            database.delete_edge(self.source, self.target, self.key, self.kind)
            if auto_commit:
                database.commit()

class NodeKindOperation(Operation):
    operation: Literal[
        "nodekind.add",
        "nodekind.update",
        "nodekind.delete",
    ] = Field(...)

class AddNodeKindOperation(NodeKindOperation):
    operation: Literal["nodekind.add"] = Field("nodekind.add")
    data: dict = Field(...)
    python: str = Field(...)

    def execute(
        self,
        graph: Union['StoryGraph',None]=None,
        database: Database|None=None,
        auto_commit: bool=True,
    ):
        key = self.data.get('key')
        if not key:
            raise StoryGraphError('key is required')
        if key in NODEKINDS:
            raise StoryGraphError(f'duplicate key: "{key}"')

        hydrated = NodeKindTransport.hydrate(self.data)
        if not hydrated:
            raise StoryGraphError(f'invalid data: "{self.data}"')

        node_kind = NodeKind(
            key=hydrated.key,
            label=hydrated.label or hydrated.key,
            title=hydrated.title or hydrated.label,
            description=hydrated.description or '',
            category=hydrated.category or 'default',
            allowed_connections=hydrated.allowed_connections or {'node':['node']},
            transport_class=type(hydrated.transport_class) or 'NodeTransport',
        )
        NODEKINDS[key] = node_kind

        if database:
            database.replace_node_kind(key, node_kind.dump())
            if auto_commit:
                database.commit()

class UpdateNodeKindOperation(NodeKindOperation):
    operation: Literal["nodekind.update"] = Field("nodekind.update")
    data: dict = Field(...)

    def execute(
        self,
        graph: Union['StoryGraph',None]=None,
        database: Database|None=None,
        auto_commit: bool=True,
    ):
        key = self.data.get('key')
        if not key:
            raise StoryGraphError('key is required')
        if not key in NODEKINDS:
            raise StoryGraphError(f'not found: "{key}"')

        hydrated = NodeKindTransport.hydrate(self.data)
        if not hydrated:
            raise StoryGraphError(f'invalid data: "{self.data}"')

        node_kind = NODEKINDS[key]
        updated = node_kind.model_copy(update=hydrated, deep=True)
        NODEKINDS[key] = updated

        if database:
            database.replace_node_kind(updated)
            if auto_commit:
                database.commit()

class DeleteNodeKindOperation(NodeKindOperation):
    operation: Literal["nodekind.delete"] = Field("nodekind.delete")
    key: str = Field(...)

    def execute(
        self,
        graph: Union['StoryGraph',None]=None,
        database: Database|None=None,
        auto_commit: bool=True,
    ):
        if not key:
            raise StoryGraphError('key is required')
        if key not in NODEKINDS:
            raise StoryGraphError(f'not found: "{key}"')

        del NODEKINDS[key]

        if database:
            database.delete_node_kind(key)
            if auto_commit:
                database.commit()

class EdgeKindOperation(Operation):
    operation: Literal[
        "edgekind.add",
        "edgekind.update",
        "edgekind.delete",
    ] = Field(...)

class AddEdgeKindOperation(EdgeKindOperation):
    operation: Literal["edgekind.add"] = Field("edgekind.add")
    data: dict = Field(...)

    def execute(
        self,
        graph: Union['StoryGraph',None]=None,
        database: Database|None=None,
        auto_commit: bool=True,
    ):
        key = self.data.get('key')
        if not key:
            raise StoryGraphError('key is required')
        if key in EDGEKINDS:
            raise StoryGraphError(f'duplicate key: "{key}"')

        hydrated = EdgeKindTransport.hydrate(self.data)
        if not hydrated:
            raise StoryGraphError(f'invalid data: "{self.data}"')

        edge_kind = EdgeKind(
            key=hydrated.key,
            label=hydrated.label or hydrated.key,
            title=hydrated.title or hydrated.label,
            description=hydrated.description or '',
            category=hydrated.category or 'default',
            directed=hydrated.directed,
            transitive=hydrated.transitive,
            acyclic=hydrated.acyclic,
            multiple_allowed=hydrated.multiple_allowed,
            reverse=hydrated.reverse or '',
            allowed_connections=hydrated.allowed_connections or {'node':['node']},
            score_hint=hydrated.score_hint or '',
        )

        EDGEKINDS[key] = edge_kind

        if database:
            database.replace_edge_kind(key, edge_kind.dump())
            if auto_commit:
                database.commit()

class UpdateEdgeKindOperation(EdgeKindOperation):
    operation: Literal["edgekind.update"] = Field("edgekind.update")
    edge_kind: dict = Field(...)

    def execute(
        self,
        graph: Union['StoryGraph',None]=None,
        database: Database|None=None,
        auto_commit: bool=True,
    ):
        key = self.edge_kind.get('key')
        if not key:
            raise StoryGraphError('key is required')
        if key in EDGEKINDS:
            raise StoryGraphError(f'duplicate key: "{key}"')

        hydrated = EdgeKindTransport.hydrate(self.data)
        if not hydrated:
            raise StoryGraphError(f'invalid data: "{self.data}"')

        edge_kind = EDGEKINDS[key]
        updated = edge_kind.model_copy(update=hydrated, deep=True)

        EDGEKINDS[key] = updated

        if database:
            database.replace_edge_kind(updated)
            if auto_commit:
                database.commit()

class DeleteEdgeKindOperation(EdgeKindOperation):
    operation: Literal["edgekind.delete"] = Field("edgekind.delete")
    key: str = Field(...)

    def execute(
        self,
        graph: Union['StoryGraph',None]=None,
        database: Database|None=None,
        auto_commit: bool=True,
    ):
        if not key:
            raise StoryGraphError('key is required')
        if key not in EDGEKINDS:
            raise StoryGraphError(f'not found: "{key}"')

        del EDGEKINDS[key]

        if database:
            database.delete_edge_kind(key)
            if auto_commit:
                database.commit()



class EdgeKind(BaseModel):
    """
    Definition of a semantic edge type in the story graph.

    An `EdgeKind` describes how two nodes can be related: containment,
    causality, participation, thematic linkage, etc. It encodes:
    - identity and human-readable metadata,
    - structural constraints (directed, acyclic, transitive),
    - weight bounds and defaults,
    - allowed source/target node types,
    - optional property definitions for edges of this kind.
    """

    key: str = Field(
        ...,
        description=(
            "Short internal key identifying this edge kind in code and data. "
            "Used as the primary lookup key in edge-kind registries."
        ),
    )
    label: str = Field(
        ...,
        description=(
            "Human-facing label for this edge kind (e.g. 'Contains', 'Causes'). "
            "Used in UI and diagram rendering."
        ),
    )
    title: str = Field(
        ...,
        description=(
            "Longer descriptive title summarizing the role of this edge kind "
            "in the narrative/simulation model."
        ),
    )
    description: str = Field(
        ...,
        description=(
            "Detailed explanation of what the edge represents conceptually, "
            "including narrative and simulation semantics."
        ),
    )
    category: Literal[""] = Field(
        "",
        description=(
            "High-level category or namespace for this edge kind. "
            "Currently only `default` is used, but this allows future grouping."
        ),
    )
    directed: bool = Field(
        True,
        description=(
            "Whether edges of this kind are directional (`True`) or symmetric (`False`). "
            "If `False`, source/target are treated as an unordered pair."
        ),
    )
    transitive: bool = Field(
        False,
        description=(
            "Whether the relation is considered transitive for inference "
            "and traversal (e.g. if A→B and B→C, then A→C)."
        ),
    )
    acyclic: bool = Field(
        True,
        description=(
            "Whether cycles are forbidden for this edge kind. "
            "If `True`, the graph should not contain A→…→A along this kind."
        ),
    )
    multiple_allowed: bool = Field(
        False,
        description=(
            "If `True`, multiple edges of this kind may exist between the same "
            "pair of nodes. If `False`, at most one such edge should exist."
        ),
    )
    reverse: str = Field('')
    allowed_connections: Dict[str, List[str]] = Field(
        default_factory=lambda: {"*": ["*"]},
        description=(
            "Mapping from allowed source node types to a list of allowed target "
            "node types. Keys and values are type names (e.g. 'Scene', 'Character'). "
            "A wildcard `'*'` permits any type."
        ),
    )
    score_hint: str = Field(
        "",
        description=(
            "Free-form hint describing how weights for this edge kind should be "
            "interpreted by scoring, simulation, or layout algorithms."
        ),
    )
    transport_class: type = Field(EdgeTransport)

    def model_post_init(self, __context: Any) -> None:
        """
        Derive missing identifiers and enforce minimal invariants.

        - Ensures `key` is non-empty; raises `ValueError('key')` otherwise.
        - If `id` is empty, derives it as `edgekind:{key}`.
        """
        super().model_post_init(__context)

        if not self.key:
            raise ValueError("key")

    def dump(self) -> Dict[str,Any]:
        return self.model_dump(exclude=['transport_class'], exclude_unset=True, exclude_none=True)

class EdgeKinds:
    @staticmethod
    def get(kind: str):
        if kind not in EDGEKINDS:
            raise RuntimeError('kind')
        return EDGEKINDS[kind]

    Contains: EdgeKind = EdgeKind(
        key="contains",
        label="Contains",
        title="Structural Containment",
        description="Hierarchical membership (story→chapter→scene→beat→event). Direction: parent → child.",
        category="",
        directed=True,
        transitive=True,
        acyclic=True,
        multiple_allowed=True,
        reverse='contains',
        allowed_connections={
            "node": ["node"],
        },
        score_hint="Weight ignored for traversal cost; used for layout strength.",
        transport_class=EdgeTransport,
    )
    Indexes: EdgeKind = EdgeKind(
        key="indexes",
        label="Indexes",
        title="Discourse Indexing",
        description="Assigns an ordering/index node to another node (e.g., chapter indexing scenes).",
        category="",
        directed=True,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Chapter": ["Scene", "Beat"],
            "Thread": ["Scene", "Beat"],
        },
        score_hint="Higher weight = stronger placement authority.",
        transport_class=EdgeTransport,
    )
    InFabulaOf: EdgeKind = EdgeKind(
        key="in_fabula_of",
        label="In Fabula Of",
        title="Chronological Belonging",
        description="Places node in the in-world (fabula) timeline container.",
        category="",
        directed=True,
        transitive=False,
        acyclic=True,
        multiple_allowed=False,
        allowed_connections={
            "Scene": ["Timeline:Fabula"],
            "Beat": ["Timeline:Fabula"],
            "Event": ["Timeline:Fabula"],
        },
        score_hint="Used to resolve chronological queries; weight = timestamp certainty.",
        transport_class=EdgeTransport,
    )
    InDiscourseOf: EdgeKind = EdgeKind(
        key="in_discourse_of",
        label="In Discourse Of",
        title="Narrative Order Placement",
        description="Places node in told-order (discourse) sequence container.",
        category="",
        directed=True,
        transitive=False,
        acyclic=True,
        multiple_allowed=False,
        allowed_connections={
            "Scene": ["Timeline:Discourse"],
            "Beat": ["Timeline:Discourse"],
            "Event": ["Timeline:Discourse"],
        },
        score_hint="Used for rendering/reading order; weight = confidence.",
        transport_class=EdgeTransport,
    )
    Causes: EdgeKind = EdgeKind(
        key="causes",
        label="Causes",
        title="Causal Influence",
        description="Source produces or materially contributes to target.",
        category="",
        directed=True,
        transitive=True,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "node": ["node"],
        },
        score_hint="Weight = strength of causation used in propagation.",
        transport_class=EdgeTransport,
    )
    RelatedTo: EdgeKind = EdgeKind(
        key="related_to",
        label="Related To",
        title="Relationship Link",
        description="General social/emotional tie (baseline bond).",
        category="",
        directed=False,
        transitive=False,
        acyclic=False,
        multiple_allowed=False,
        allowed_connections={
            "Character": ["Character", "Place", "Object"],
            "Place": ["Character", "Place", "Object"],
            "Object": ["Character", "Place", "Object"],
        },
        score_hint="Weight seeds relationship metrics.",
        transport_class=RelatedToEdgeTransport,
    )
    HasArc: EdgeKind = EdgeKind(
        key="has_arc",
        label="Has Arc",
        title="",
        description="",
        category="",
        directed=True,
        transitive=False,
        acyclic=True,
        multiple_allowed=False,
        allowed_connections={
            "node": ["arc"],
        },
        score_hint="weight = progress",
        transport_class=EdgeTransport,
    )
    ArcStage: EdgeKind = EdgeKind(
        key="arcstage",
        label="ArcStage",
        title="",
        description="",
        category="",
        directed=True,
        transitive=False,
        acyclic=True,
        multiple_allowed=False,
        allowed_connections={
            "arc": ["arcstage"],
        },
        score_hint="weight = progress",
        transport_class=EdgeTransport,
    )
    Follows: EdgeKind = EdgeKind(
        key="follows",
        label="Follows",
        title="",
        description="",
        category="",
        directed=True,
        transitive=True,
        acyclic=True,
        multiple_allowed=False,
        allowed_connections={
            "node": ["node"],
        },
        transport_class=EdgeTransport,
    )

EDGEKINDS: Dict[str, EdgeKind] = {
    # === Structural ==========================================================
    "contains": EdgeKinds.Contains,
    "indexes": EdgeKinds.Indexes,
    "in_fabula_of": EdgeKinds.InFabulaOf,
    "in_discourse_of": EdgeKinds.InDiscourseOf,
    # === Causal ==============================================================
    "causes": EdgeKinds.Causes,
    "enabled_by": EdgeKind(
        key="enabled_by",
        label="Enabled By",
        title="Enabling Condition",
        description="Target is possible only because source removed a constraint or supplied a prerequisite.",
        category="",
        directed=True,
        weight_default=0.6,
        weight_min=0.1,
        weight_max=1.0,
        transitive=True,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Event": ["Event", "Goal", "Tactic"],
            "State": ["Event", "Goal", "Tactic"],
            "Goal": ["Event", "Goal", "Tactic"],
            "Tactic": ["Event", "Goal", "Tactic"],
        },
        score_hint="Weight contributes to feasibility scoring.",
    ),
    "follows": EdgeKind(
        key="follows",
        label="Follows",
        title="Temporal Succession",
        description="Target occurs after source (local sequence without strong causality).",
        category="",
        directed=True,
        weight_default=0.4,
        weight_min=0.0,
        weight_max=0.8,
        transitive=True,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Event": ["Event", "Beat", "Scene"],
            "Beat": ["Event", "Beat", "Scene"],
            "Scene": ["Event", "Beat", "Scene"],
        },
        score_hint="Weight = adjacency tightness; weakly influences traversal.",
    ),
    "triggers": EdgeKind(
        key="triggers",
        label="Triggers",
        title="Trigger Relation",
        description="Source stimulus initiates target reaction (often affective/arc transitions).",
        category="",
        directed=True,
        weight_default=0.65,
        weight_min=0.2,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Event": ["ArcTransition", "ArcState", "Event"],
            "Beat": ["ArcTransition", "ArcState", "Event"],
            "Scene": ["ArcTransition", "ArcState", "Event"],
        },
        score_hint="Weight biases transition evidence.",
    ),
    "inhibits": EdgeKind(
        key="inhibits",
        label="Inhibits",
        title="Inhibitory Relation",
        description="Source suppresses, blocks, or reduces the likelihood of target.",
        category="",
        directed=True,
        weight_default=0.6,
        weight_min=0.1,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Event": ["Event", "Goal", "Tactic", "ArcTransition"],
            "Goal": ["Event", "Goal", "Tactic", "ArcTransition"],
            "Tactic": ["Event", "Goal", "Tactic", "ArcTransition"],
        },
        score_hint="Used as negative evidence or feasibility penalty.",
    ),
    "fulfills": EdgeKind(
        key="fulfills",
        label="Fulfills",
        title="Fulfillment",
        description="Source satisfies or completes the target requirement (e.g., event → goal).",
        category="",
        directed=True,
        weight_default=0.8,
        weight_min=0.3,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Event": ["Goal", "ArcStage"],
            "Tactic": ["Goal", "ArcStage"],
            "ArcTransition": ["Goal", "ArcStage"],
        },
        score_hint="Threshold crossing when cumulative weight ≥ criterion.",
    ),
    # === Motivational ========================================================
    "participates_in": EdgeKind(
        key="participates_in",
        label="Participates In",
        title="Participation",
        description="Character materially acts in target node (scene/beat/event).",
        category="",
        directed=True,
        weight_default=0.7,
        weight_min=0.2,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Character": ["Scene", "Beat", "Event"],
        },
        score_hint="Weight drives contribution share for outcomes.",
    ),
    "features_in": EdgeKind(
        key="features_in",
        label="Features In",
        title="Cast Membership",
        description="Character included without necessarily acting (presence or mention).",
        category="",
        directed=True,
        weight_default=0.4,
        weight_min=0.0,
        weight_max=0.8,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Character": ["Scene", "Beat"],
        },
        score_hint="Weight modulates salience in narration.",
    ),
    "focus_on": EdgeKind(
        key="focus_on",
        label="Focus On",
        title="Focalization",
        description="Scene or beat centers internal perspective on character.",
        category="",
        directed=True,
        weight_default=0.8,
        weight_min=0.3,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Scene": ["Character"],
            "Beat": ["Character"],
        },
        score_hint="Weight biases narrative distance/voice.",
    ),
    "authored": EdgeKind(
        key="authored",
        label="Authored",
        title="Authorship",
        description="Author creates/owns node (meta linkage).",
        directed=True,
        weight_default=1.0,
        weight_min=1.0,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Author": [
                "Story",
                "Chapter",
                "Scene",
                "Beat",
                "Character",
                "Theme",
                "Thread",
            ],
        },
        score_hint="Meta only; not used in simulation scoring.",
    ),
    "derives_from": EdgeKind(
        key="derives_from",
        label="Derives From",
        title="Motivational Derivation",
        description="Goal/tactic originates from underlying motivation.",
        category="",
        directed=True,
        weight_default=0.7,
        weight_min=0.2,
        weight_max=1.0,
        transitive=True,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Goal": ["Motivation"],
            "Tactic": ["Motivation"],
        },
        score_hint="Weight scales goal priority or tactic fit.",
    ),
    "advances": EdgeKind(
        key="advances",
        label="Advances",
        title="Progression",
        description="Source makes measurable progress toward target goal/arc.",
        category="",
        directed=True,
        weight_default=0.6,
        weight_min=0.1,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Event": ["Goal", "ArcState"],
            "Beat": ["Goal", "ArcState"],
            "Scene": ["Goal", "ArcState"],
            "Tactic": ["Goal", "ArcState"],
        },
        score_hint="Weight = delta magnitude toward completion.",
    ),
    "blocks": EdgeKind(
        key="blocks",
        label="Blocks",
        title="Obstruction",
        description="Source impedes target (goal/arc/tactic) from progressing.",
        category="",
        directed=True,
        weight_default=0.6,
        weight_min=0.1,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Event": ["Goal", "ArcState", "Tactic"],
            "Goal": ["Goal", "ArcState", "Tactic"],
            "Tactic": ["Goal", "ArcState", "Tactic"],
        },
        score_hint="Subtract from progress; can trigger regression.",
    ),
    "depends_on": EdgeKind(
        key="depends_on",
        label="Depends On",
        title="Dependency",
        description="Target requires source to be achieved first (goal→goal).",
        category="",
        directed=True,
        weight_default=0.75,
        weight_min=0.3,
        weight_max=1.0,
        transitive=True,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Goal": ["Goal"],
        },
        score_hint="Weight scales gating strictness.",
    ),
    "supports": EdgeKind(
        key="supports",
        label="Supports",
        title="Supportive Relation",
        description="Source aids/strengthens target pursuit (goal↔goal or goal↔tactic).",
        category="",
        directed=True,
        weight_default=0.5,
        weight_min=0.1,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Goal": ["Goal", "Tactic"],
            "Tactic": ["Goal", "Tactic"],
        },
        score_hint="Adds synergy bonus to EV of plans.",
    ),
    "utilizes": EdgeKind(
        key="utilizes",
        label="Utilizes",
        title="Means–End",
        description="Goal uses tactic as operational means; character uses tactic for goal.",
        category="",
        directed=True,
        weight_default=0.7,
        weight_min=0.2,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Goal": ["Tactic"],
            "Character": ["Tactic"],
        },
        score_hint="Weight = suitability; multiplies success odds.",
    ),
    # === Affected ============================================================
    "influences": EdgeKind(
        key="influences",
        label="Influences",
        title="Interpersonal Influence",
        description="Source character shifts target character’s affect/state.",
        category="",
        directed=True,
        weight_default=0.6,
        weight_min=0.1,
        weight_max=1.0,
        transitive=True,
        acyclic=False,
        multiple_allowed=True,
        allowed_connections={
            "Character": ["Character"],
        },
        score_hint="Weight scales affect propagation magnitude.",
    ),
    "related_to": EdgeKinds.RelatedTo,
    "conflicts_with": EdgeKind(
        key="conflicts_with",
        label="Conflicts With",
        title="Conflict",
        description="Agents’ goals collide; competitive dynamics.",
        category="",
        directed=False,
        weight_default=0.6,
        weight_min=0.0,
        weight_max=1.0,
        transitive=False,
        acyclic=False,
        multiple_allowed=True,
        allowed_connections={
            "Character": ["Character", "Place", "Object", "Motivation", "Goal"],
            "Place": ["Character", "Place", "Object", "Motivation", "Goal"],
            "Object": ["Character", "Place", "Object", "Motivation", "Goal"],
            "Motivation": ["Character", "Place", "Object", "Motivation", "Goal"],
            "Goal": ["Character", "Place", "Object", "Motivation", "Goal"],
        },
        score_hint="Weight raises tension; reduces success odds.",
    ),
    "cooperates_with": EdgeKind(
        key="cooperates_with",
        label="Cooperates With",
        title="Cooperation",
        description="Aligned efforts or mutual aid.",
        category="",
        directed=False,
        weight_default=0.0,
        weight_min=-1.0,
        weight_max=1.0,
        transitive=False,
        acyclic=False,
        multiple_allowed=True,
        allowed_connections={
            "Character": ["Character", "Place", "Object", "Motivation", "Goal"],
            "Place": ["Character", "Place", "Object", "Motivation", "Goal"],
            "Object": ["Character", "Place", "Object", "Motivation", "Goal"],
            "Motivation": ["Character", "Place", "Object", "Motivation", "Goal"],
            "Goal": ["Character", "Place", "Object", "Motivation", "Goal"],
        },
        score_hint="Weight grants synergy/tension relief.",
    ),
    # === Thematic ============================================================
    "embodies_theme": EdgeKind(
        key="embodies_theme",
        label="Embodies Theme",
        title="Thematic Embodiment",
        description="Source (char/arc/place) embodies target theme.",
        category="",
        directed=True,
        weight_default=0.7,
        weight_min=0.2,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Character": ["Theme"],
            "Arc": ["Theme"],
            "Place": ["Theme"],
            "Object": ["Theme"],
            "Thread": ["Theme"],
        },
        score_hint="Weight biases thematic labeling and summaries.",
    ),
    "engages_theme": EdgeKind(
        key="engages_theme",
        label="Engages Theme",
        title="Thematic Engagement",
        description="Scene/beat/event explicitly tests or foregrounds theme.",
        category="",
        directed=True,
        weight_default=0.6,
        weight_min=0.1,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Scene": ["Theme"],
            "Beat": ["Theme"],
            "Event": ["Theme"],
        },
        score_hint="Higher weight increases theme salience scoring.",
    ),
    "contrasts_with": EdgeKind(
        key="contrasts_with",
        label="Contrasts With",
        title="Thematic Contrast",
        description="Juxtaposes opposing ideas or arcs.",
        category="",
        directed=False,
        weight_default=0.5,
        weight_min=0.0,
        weight_max=1.0,
        transitive=False,
        acyclic=False,
        multiple_allowed=True,
        allowed_connections={
            "Theme": ["Theme", "Arc", "Scene"],
            "Arc": ["Theme", "Arc", "Scene"],
            "Scene": ["Theme", "Arc", "Scene"],
        },
        score_hint="Weight heightens dialectical reading and tension.",
    ),
    "symbolizes": EdgeKind(
        key="symbolizes",
        label="Symbolizes",
        title="Symbolic Representation",
        description="Object/place symbolizes abstract concept or theme.",
        category="",
        directed=True,
        weight_default=0.7,
        weight_min=0.2,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Place": ["Theme"],
            "Prop": ["Theme"],
            "Motif": ["Theme"],
        },
        score_hint="Weight drives metaphor density in prose.",
    ),
    "reflects": EdgeKind(
        key="reflects",
        label="Reflects",
        title="Mirror Relation",
        description="Subplot/arc reflects or echoes another arc/scene.",
        category="",
        directed=False,
        weight_default=0.5,
        weight_min=0.1,
        weight_max=1.0,
        transitive=False,
        acyclic=False,
        multiple_allowed=True,
        allowed_connections={
            "Arc": ["Arc", "Scene", "Thread"],
            "Scene": ["Arc", "Scene", "Thread"],
            "Thread": ["Arc", "Scene", "Thread"],
        },
        score_hint="Used for structural mirroring and callbacks.",
    ),
    # === Narrative Flow ======================================================
    "sets_up": EdgeKind(
        key="sets_up",
        label="Sets Up",
        title="Foreshadowing Setup",
        description="Source plants information or tension paid off later.",
        category="",
        directed=True,
        weight_default=0.6,
        weight_min=0.1,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Beat": ["Beat", "Scene"],
            "Scene": ["Beat", "Scene"],
            "Thread": ["Beat", "Scene"],
        },
        score_hint="Paired with PAYS_OFF; sum weights → payoff strength.",
    ),
    "pays_off": EdgeKind(
        key="pays_off",
        label="Pays Off",
        title="Payoff",
        description="Source resolves, reveals, or rewards an earlier setup.",
        category="",
        directed=True,
        weight_default=0.7,
        weight_min=0.2,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Beat": ["Beat", "Scene"],
            "Scene": ["Beat", "Scene"],
        },
        score_hint="Weight boosts reader satisfaction metrics.",
    ),
    "calls_back_to": EdgeKind(
        key="calls_back_to",
        label="Calls Back To",
        title="Callback",
        description="Source evokes a prior node for resonance or humor.",
        category="",
        directed=True,
        weight_default=0.5,
        weight_min=0.0,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Beat": ["Beat", "Scene", "Line"],
            "Scene": ["Beat", "Scene", "Line"],
            "Line": ["Beat", "Scene", "Line"],
        },
        score_hint="Weight modulates echo intensity in narration.",
    ),
    "transitions_to": EdgeKind(
        key="transitions_to",
        label="Transitions To",
        title="Continuity Transition",
        description="Source shifts into target (time/place/mood).",
        category="",
        directed=True,
        weight_default=0.5,
        weight_min=0.0,
        weight_max=1.0,
        transitive=True,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Scene": ["Scene", "Beat"],
            "Beat": ["Scene", "Beat"],
        },
        score_hint="Weight lowers perceived jump harshness.",
    ),
    # === Meta ================================================================
    "propagates_to": EdgeKind(
        key="propagates_to",
        label="Propagates To",
        title="Affect/State Propagation",
        description="State change at source diffuses into target during update steps.",
        category="",
        directed=True,
        weight_default=0.5,
        weight_min=0.0,
        weight_max=1.0,
        transitive=True,
        acyclic=False,
        multiple_allowed=True,
        allowed_connections={
            "Character": ["Character", "Relationship", "ArcState"],
            "Relationship": ["Character", "Relationship", "ArcState"],
            "ArcState": ["Character", "Relationship", "ArcState"],
        },
        score_hint="Weight is multiplier on delta magnitude.",
    ),
    "state_depends_on": EdgeKind(
        key="state_depends_on",
        label="State Depends On",
        title="State Dependency",
        description="Target variable computed from source variable(s).",
        category="",
        directed=True,
        weight_default=0.8,
        weight_min=0.3,
        weight_max=1.0,
        transitive=True,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Goal": ["Goal", "Motivation", "ArcState", "Relationship"],
            "Motivation": ["Goal", "Motivation", "ArcState", "Relationship"],
            "ArcState": ["Goal", "Motivation", "ArcState", "Relationship"],
            "Relationship": ["Goal", "Motivation", "ArcState", "Relationship"],
        },
        score_hint="Weight tunes sensitivity in recompute.",
    ),
    "observed_by": EdgeKind(
        key="observed_by",
        label="Observed By",
        title="Perception Link",
        description="Source event/scene was witnessed by target character.",
        category="",
        directed=True,
        weight_default=0.7,
        weight_min=0.2,
        weight_max=1.0,
        transitive=False,
        acyclic=True,
        multiple_allowed=True,
        allowed_connections={
            "Event": ["Character"],
            "Scene": ["Character"],
        },
        score_hint="Weight raises knowledge/belief update chance.",
    ),
    "knows_of": EdgeKind(
        key="knows_of",
        label="Knows Of",
        title="Knowledge Relation",
        description="Source character is aware of target node (fact/goal/event).",
        category="",
        directed=True,
        weight_default=0.6,
        weight_min=0.1,
        weight_max=1.0,
        transitive=True,
        acyclic=False,
        multiple_allowed=True,
        allowed_connections={
            "Character": ["Character", "Goal", "Event", "Fact"],
        },
        score_hint="Weight affects planning search space.",
    ),
    "believes_about": EdgeKind(
        key="believes_about",
        label="Believes About",
        title="Belief Model",
        description="Source character holds a belief regarding target (character/goal/world).",
        category="",
        directed=True,
        weight_default=0.5,
        weight_min=-1.0,
        weight_max=1.0,
        transitive=False,
        acyclic=False,
        multiple_allowed=True,
        allowed_connections={
            "Character": ["Character", "Goal", "Motivation", "Fact"],
        },
        score_hint="Weight is belief certainty/valence.",
    ),
    "version_of": EdgeKind(
        key="version_of",
        label="Version Of",
        title="Versioning Link",
        description="Source is a draft/variant/retelling of target.",
        category="",
        directed=True,
        weight_default=1.0,
        weight_min=0.0,
        weight_max=1.0,
        transitive=True,
        acyclic=False,
        multiple_allowed=True,
        allowed_connections={
            "Story": ["Story", "Scene", "Beat", "Line"],
            "Scene": ["Story", "Scene", "Beat", "Line"],
            "Beat": ["Story", "Scene", "Beat", "Line"],
            "Line": ["Story", "Scene", "Beat", "Line"],
        },
        score_hint="Weight encodes similarity; not causal.",
    ),
}

class NodeKind(BaseModel):
    """
    Definition of a semantic node type in the story graph.
    """

    key: str = Field(
        ...,
        description=(
            "Short internal key identifying this node kind in code and data. "
            "Used as the primary lookup key in node-kind registries."
        ),
    )
    label: str = Field(
        ...,
        description=(
            "Human-facing label for this node kind (e.g. 'Contains', 'Causes'). "
            "Used in UI and diagram rendering."
        ),
    )
    title: str = Field(
        ...,
        description=(
            "Longer descriptive title summarizing the role of this node kind "
            "in the narrative/simulation model."
        ),
    )
    description: str = Field(
        ...,
        description=(
            "Detailed explanation of what the node represents conceptually, "
            "including narrative and simulation semantics."
        ),
    )
    category: Literal["", 'narrative', 'focus'] = Field(
        "",
        description=(
            "High-level category or namespace for this node kind. "
            "Currently only `` is used, but this allows future grouping."
        ),
    )
    allowed_connections: Dict[str, List[str]] = Field(default_factory=dict)
    transport_class: type = Field(NodeTransport)
    required_edges: List[str] = Field(default_factory=list)
    affective: bool = Field(False)

    def model_post_init(self, __context: Any) -> None:
        """
        Derive missing identifiers and enforce minimal invariants.

        - Ensures `key` is non-empty; raises `ValueError('key')` otherwise.
        - If `id` is empty, derives it as `nodekind:{key}`.
        """
        super().model_post_init(__context)

        if not self.key:
            raise ValueError("key")

    def dump(self) -> Dict[str,Any]:
        return self.model_dump(exclude=['transport_class'], exclude_unset=True, exclude_none=True)

class NodeKinds:
    @staticmethod
    def get(kind: str):
        if kind not in NODEKINDS:
            raise RuntimeError('kind')
        return NODEKINDS[kind]

    Node: NodeKind = NodeKind(
        key="node",
        label="Node",
        title="A Node",
        description="",
        category="",
        allowed_connections={
            'has_arc': ['arc'],
            'has_relation': ['node'],
        },
        transport_class=NodeTransport,
        affective=True,
    )
    Arc: NodeKind = NodeKind(
        key="arc",
        label="Arc",
        title="An Arc",
        description="",
        category="",
        allowed_connections=Node.allowed_connections|{
            'owner': ['node'],
            'arcstage': ['arcstage'],
            'theme': ['theme'],
            },
        transport_class=ArcTransport,
    )
    ArcStage: NodeKind = NodeKind(
        key="arcstage",
        label="ArcStage",
        title="An Arc Stage",
        description="",
        category="",
        allowed_connections={
            'arc': ['arc'],
            'follows': ['arcstage'],
            },
        transport_class=ArcStageTransport,
    )
    Story: NodeKind = NodeKind(
        key="story",
        label="Story",
        title="A Story",
        description="",
        category="narrative",
        transport_class=StoryTransport,
        affective=True,
    )
    Scene: NodeKind = NodeKind(
        key="story",
        label="Story",
        title="A Story",
        description="",
        category="narrative",
        transport_class=SceneTransport,
        affective=True,
    )
    Beat: NodeKind = NodeKind(
        key="beat",
        label="Beat",
        title="A Beat",
        description="",
        category="narrative",
        transport_class=BeatTransport,
        affective=True,
    )
    Character: NodeKind = NodeKind(
        key="character",
        label="Character",
        title="A Character",
        description="",
        category="focus",
        transport_class=CharacterTransport,
        affective=True,
    )
    Place: NodeKind = NodeKind(
        key="place",
        label="Place",
        title="A Place",
        description="",
        category="focus",
        transport_class=PlaceTransport,
        affective=True,
    )
    Thing: NodeKind = NodeKind(
        key="thing",
        label="Thing",
        title="A Thing",
        description="",
        category="focus",
        transport_class=ThingTransport,
        affective=True,
    )
    Motivation: NodeKind = NodeKind(
        key="motivation",
        label="Motivation",
        title="A Motivation",
        description="",
        category="focus",
        transport_class=MotivationTransport,
        affective=True,
    )

NODEKINDS: Dict[str, NodeKind] = {
    'node': NodeKinds.Node,
    'arc': NodeKinds.Arc,
    'arcstage': NodeKinds.ArcStage,
    'story': NodeKinds.Story,
    'scene': NodeKinds.Scene,
    'beat': NodeKinds.Beat,
    'character': NodeKinds.Character,
    'place': NodeKinds.Place,
    'thing': NodeKinds.Thing,
    'motivation': NodeKinds.Motivation,
}



class Project(BaseModel):
    title: str = Field(...)
    filename: str = Field('')

    database: Union[Database,None] = Field(None)
    graph: Union[StoryGraph,None] = Field(None)
    nodekinds: Dict[str,NodeKind] = Field(default_factory=dict)
    edgekinds: Dict[str,EdgeKind] = Field(default_factory=dict)
    affectdefs: Dict[str,AffectDefinition] = Field(default_factory=dict)

    def model_post_init(self, __context: Any) -> None:
        super().model_post_init(__context)

        if not self.title:
            raise ValueError("title")

        if not self.filename:
            self.filename = f'{self.title}.sqlite'

        if not self.database:
            self.database = Database(self.filename)

        if not self.graph:
            self.graph = StoryGraph(project=self, database=self.database)

        self.prepare_database()

    def prepare_database(self):
        self.database.connection.execute(
            """CREATE TABLE IF NOT EXISTS "nodes" (
                "id"	TEXT NOT NULL,
                "k"	TEXT NOT NULL,
                "d"	TEXT NOT NULL,
                "ts" TEXT,
                PRIMARY KEY("id","k")
            );""")

        self.database.connection.execute(
            """CREATE TABLE IF NOT EXISTS "edges" (
                "s"	TEXT NOT NULL,
                "t"	TEXT NOT NULL,
                "i"	INTEGER NOT NULL,
                "k"	TEXT NOT NULL,
                "d"	TEXT,
                "ts" TEXT,
                PRIMARY KEY("s","t","i")
            );""")

        self.database.connection.execute(
            """CREATE TABLE IF NOT EXISTS "nodekinds" (
                "k"	TEXT NOT NULL,
                "d"	TEXT,
                "ts" TEXT,
                PRIMARY KEY("k")
            );""")

        self.database.connection.execute(
            """CREATE TABLE IF NOT EXISTS "edgekinds" (
                "k"	TEXT NOT NULL,
                "d"	TEXT,
                "ts" TEXT,
                PRIMARY KEY("k")
            );""")

        self.database.connection.execute(
            """CREATE TABLE IF NOT EXISTS "affects" (
                "k"	TEXT NOT NULL,
                "d"	TEXT,
                "ts" TEXT,
                PRIMARY KEY("k")
            );""")

        for key,edgekind in self.edgekinds.items():
            try:
                self.database.insert_edge_kind(key, edgekind.dump())
            except DatabaseError:
                pass

        for key,nodekind in self.nodekinds.items():
            try:
                self.database.insert_node_kind(key, nodekind.dump())
            except DatabaseError:
                pass

        for key,affectdef in self.affectdefs.items():
            try:
                self.database.insert_affect(key, affectdef.dump())
            except DatabaseError:
                pass

        self.database.commit()

    def dump(self) -> Dict[str,Any]:
        return self.model_dump(exclude=['transport_class'], exclude_unset=True, exclude_none=True)

    model_config = ConfigDict(extra='allow', arbitrary_types_allowed=True)

    def add_node(self, key:str, kind:str, data:dict={}):
        if not key:
            raise StoryGraphError('key is required')
        if self.graph.has_node(key):
            raise StoryGraphError(f'duplicate key: {key}')
        if not kind:
            raise StoryGraphError('kind is required')
        if kind not in self.nodekinds:
            raise StoryGraphError(f'kind not found: {kind}')
        node = dict(data or {})
        node['key'] = key
        node['kind'] = kind
        self.graph.add_node(key, node)

    def add_story(self, key:str, title:str='', subtitle:str='', summary:str=''):
        self.add_node(key, 'story', {'title': title, 'subtitle': subtitle, 'summary': summary})

    def add_scene(self, key:str, title:str='', subtitle:str='', summary:str=''):
        self.add_node(key, 'scene', {'title': title, 'subtitle': subtitle, 'summary': summary})

    def add_beat(self, key:str, title:str='', subtitle:str='', summary:str=''):
        self.add_node(key, 'beat', {'title': title, 'subtitle': subtitle, 'summary': summary})

    def add_character(self, key:str, name:str='', role:str='', who:str=''):
        self.add_node(key, 'character', {'name': name, 'role': role, 'who': who})

    def add_place(self, key:str, name:str='', role:str='', where:str=''):
        self.add_node(key, 'place', {'name': name, 'role': role, 'where': where})

    def add_thing(self, key:str, name:str='', role:str='', what:str=''):
        self.add_node(key, 'thing', {'name': name, 'role': role, 'what': what})

    def add_motivation(self, key:str, name:str='', role:str='', why:str=''):
        self.add_node(key, 'motivation', {'name': name, 'role': role, 'why': why})

    def add_arc(self, key:str, truth:str='', lie:str=''):
        self.add_node(key, 'arc', {'truth': truth, 'lie': lie})

    def add_arcstage(self, key:str, stage:str=''):
        self.add_node(key, 'arcstage', {'stage': stage})



class StoryGraph(BaseModel):
    """
    Core in-memory representation of a story graph (NetworkX view).

    This model provides a thin, Pydantic-wrapped interface around a NetworkX
    `MultiDiGraph` plus a set of cached per-kind `DiGraph` views. It does NOT
    store full `Node`/`Edge` Pydantic objects; instead, it focuses on structural
    relationships for fast querying and analysis.

    - `graph`   : NetworkX `MultiDiGraph` containing all nodes and edges.
    - `graphs`  : per-edge-kind `DiGraph` caches (e.g. only causal edges).
    - `dirty`   : flags indicating which per-kind graphs need to be rebuilt.
    - `operations`: history or queue of structured `StoryGraphOperation`s.
    - `database`: optional backing database for persistence.
    """

    model_config = ConfigDict(arbitrary_types_allowed=True)

    operations: List[Operation] = Field(
        default_factory=list,
        description=(
            "History or queue of applied story-graph operations "
            "(insert/update/delete). Can be used for auditing, undo, "
            "or external tooling."
        ),
    )

    database: Optional[Database] = Field(
        None,
        description=(
            "Optional backing database used to persist node/edge changes. "
            "If set, higher-level code is expected to mirror graph mutations "
            "to this database."
        ),
    )

    graph: nx.MultiDiGraph = Field(
        default_factory=nx.MultiDiGraph,
        exclude=True,
        description=(
            "Runtime NetworkX MultiDiGraph containing all nodes and edges in "
            "the story graph. This is the primary structure used for queries "
            "and algorithms."
        ),
    )

    graphs: Dict[str, nx.DiGraph] = Field(
        default_factory=dict,
        exclude=True,
        description=(
            "Cached per-kind NetworkX DiGraphs. Maps edge kind id → DiGraph "
            "that includes all nodes but only edges of that kind. "
            "These views are rebuilt lazily when their dirty flag is set."
        ),
    )

    dirty: Dict[str, bool] = Field(
        default_factory=dict,
        exclude=True,
        description=(
            "Dirty flags for per-kind graphs. Maps edge kind id → True if the "
            "corresponding cached DiGraph must be rebuilt from the main "
            "MultiDiGraph before use."
        ),
    )

    project: Project = Field(...)

    def get_graph(self, kind_id: str) -> nx.MultiDiGraph | nx.DiGraph:
        """
        Return a NetworkX view of the story graph.

        - If `kind_id` is empty, returns the full `MultiDiGraph` containing
          all edges.
        - If `kind_id` is a valid edge kind, returns a cached `DiGraph`
          containing the same nodes but only edges of that kind. The cache
          is rebuilt if marked dirty or not yet created.

        Raises:
            StoryGraphError: if `kind_id` is non-empty and not a known edge kind.
        """
        if not kind_id:
            return self.graph

        if kind_id not in project.edgekinds:
            raise StoryGraphError(f'invalid edge kind: "{kind_id}"')

        if self.dirty.get(kind_id, True) or kind_id not in self.graphs:
            G = self.graphs.get(kind_id) or nx.DiGraph()
            G.clear()

            for node_id, data in self.graph.nodes(data=True):
                G.add_node(node_id, **data)

            for source, target, kind, data in self.graph.edges(keys=True, data=True):
                if kind == kind_id:
                    G.add_edge(source, target, **data)

            self.graphs[kind_id] = G
            self.dirty[kind_id] = False

        return self.graphs[kind_id]

    def has_node(self, node_id: str) -> bool:
        return self.graph.has_node(node_id)

    def get_node(self, node_id: str):
        """
        Retrieve the attribute mapping for a node in the NetworkX graph.

        Parameters:
            node_id: Identifier of the node to look up.

        Returns:
            A dict-like mapping of node attributes if the node exists,
            or None if the node is not present in the graph.
        """
        if not self.graph.has_node(node_id):
            return None
        return self.graph.nodes[node_id]

    def add_node(self, node_id: str, attrs: Optional[Dict[str, Any]] = None) -> bool:
        """
        Add (or update) a node in the NetworkX graph.

        Parameters:
            node_id: Stable node identifier.
            attrs  : Optional dict of node attributes to store on the NX node.

        Returns:
            True if the node was newly inserted, False if it already existed
            and its attributes were simply updated/overwritten.

        Raises:
            StoryGraphError: if `node_id` is empty or falsy.
        """
        if not node_id:
            raise StoryGraphError(f'invalid node_id: "{node_id}"')

        inserted = not self.graph.has_node(node_id)

        attributes = dict(attrs or {})
        attributes.setdefault('kind', 'node')

        node_kind = self.project.nodekinds.get(attributes['kind'])
        if not node_kind:
            raise StoryGraphError(f'invalid node kind: "{node_kind}"')

        node_transport = NodeTransport.hydrate(attributes)
        if not node_transport:
            raise StoryGraphError(f'invalid node: "{node_id}"')

        edges = node_transport.edges or {}
        node_transport.edges = None

        attributes = node_transport.dump()

        self.graph.add_node(node_id, **attributes)

        for edge_kind, kind in edges.items():
            for target, data in kind.items():
                self.add_edge(edge_kind, node_id, target, attrs=data)

        if self.database:
            self.database.insert_node(node_id, attributes['kind'], attributes)
            self.database.commit()

        return inserted

    def remove_node(self, node_id: str) -> bool:
        """
        Remove a node from the NetworkX graph.

        Also marks all per-kind cached graphs as dirty, since any of them
        may contain edges connected to this node.

        Parameters:
            node_id: Identifier of the node to remove.

        Returns:
            True if the node existed and was removed, False if it did not exist.
        """
        if not self.graph.has_node(node_id):
            return False

        self.graph.remove_node(node_id)

        for k in self.dirty.keys():
            self.dirty[k] = True

        return True

    def get_edge(self, source_id: str, target_id: str, kind_id: str):
        """
        Retrieve the attribute mapping for a specific edge.

        Parameters:
            source_id: Source node id.
            target_id: Target node id.
            kind_id  : Edge kind id (used as the MultiDiGraph edge key).

        Returns:
            A dict-like mapping of edge attributes if the edge exists,
            or None if the edge is not present in the graph.
        """
        if not self.graph.has_edge(source_id, target_id, kind_id):
            return None
        return self.graph.edges[source_id, target_id, kind_id]

    def add_edge(
        self,
        kind_id: str,
        source_id: str,
        target_id: str,
        key: Any = None,
        attrs: Optional[Dict[str, Any]] = None,
        auto_add_reverse: bool = False,
    ) -> bool:
        """
        Add an edge to the NetworkX graph, keyed by edge kind.

        Edges are stored in the underlying `MultiDiGraph` with the edge key
        equal to `kind_id`, so there can be at most one edge of a given kind
        between a `(source_id, target_id)` pair.

        Parameters:
            kind_id  : Edge kind identifier (must exist in `EDGE_KIND`).
            source_id: Source node id.
            target_id: Target node id.
            attrs    : Optional attribute dict stored on the edge.

        Returns:
            True if the edge was newly inserted, False if an edge with
            the same `(source_id, target_id, kind_id)` already existed.

        Raises:
            StoryGraphError: if `kind_id` is invalid or `source_id` / `target_id`
                             are empty or falsy.
        """
        if kind_id not in self.project.edgekinds:
            raise StoryGraphError(f'invalid edge kind: "{kind_id}"')

        if not source_id:
            raise StoryGraphError(f'invalid source_id: "{source_id}"')

        if not target_id:
            raise StoryGraphError(f'invalid target_id: "{target_id}"')

        source = self.get_node(source_id)
        if not source:
            raise StoryGraphError(f'source node not found: "{source_id}"')
        source_kind = source['kind']

        target = self.get_node(target_id)
        if not target:
            raise StoryGraphError(f'target node not found: "{target_id}"')
        target_kind = target['kind']

        print(f'[{kind_id}] {source_kind}:{source_id} -> {target_kind}:{target_id}')

        edge_kind = self.project.edgekinds[kind_id]
        targets = edge_kind.allowed_connections.get(source_kind, []) + edge_kind.allowed_connections.get('node', [])
        print(targets)
        if targets and target_kind not in targets and 'node' not in targets:
            raise StoryGraphError(f'connection not allowed: "{kind_id}: {source_kind} -> {target_kind}"')

        attributes = dict(attrs or {})
        attributes['source'] = source_id
        attributes['source_kind'] = source_kind
        attributes['target'] = target_id
        attributes['target_kind'] = target_kind
        attributes['kind'] = kind_id

        edge_transport = EdgeTransport.hydrate(attributes)
        if not edge_transport:
            raise StoryGraphError(f'invalid edge: "{source_id} {target_id} {kind_id}"')

        attributes = edge_transport.dump()

        if not key:
            key = self.graph.new_edge_key(source_id, target_id)

        inserted = not self.graph.has_edge(source_id, target_id, key=key)

        self.graph.add_edge(source_id, target_id, key=key, **attributes)

        if self.database:
            self.database.replace_edge(source_id, target_id, key, kind_id, attributes)

        self.dirty[kind_id] = True

        if auto_add_reverse:
            reverse = self.project.edgekinds.get(edge_kind.reverse)
            if reverse:
                attributes['source'] = target_id
                attributes['source_kind'] = target_kind
                attributes['target'] = source_id
                attributes['target_kind'] = source_kind
                attributes['kind'] = edge_kind.reverse
                key = self.graph.new_edge_key(target_id, source_id)
                self.graph.add_edge(target_id, source_id, key=key, **attributes)
                if self.database:
                    self.database.replace_edge(target_id, source_id, key, edge_kind.reverse, attributes)

        if self.database:
            self.database.commit()

        return inserted

    def remove_edge(self, kind_id: str, source_id: str, target_id: str, key: Any = None,) -> bool:
        """
        Remove a specific edge from the NetworkX graph.

        Parameters:
            source_id: Source node id.
            target_id: Target node id.
            kind_id  : Edge kind id (used as the MultiDiGraph edge key).

        Returns:
            True if the edge existed and was removed, False otherwise.
        """
        if key == None:
            edges = []
            for s, t, k, d in self.graph.out_edges(source_id, keys=True, data=True):
                if t==target_id and (not kind_id or d['kind']==kind_id):
                    edges.append((s, t, k))
            if not edges:
                return False
            self.graph.remove_edges_from(edges)
        elif not kind_id or self.graph.edges[source_id, target_id, key]['kind'] == kind_id:
            self.graph.remove_edge(source_id, target_id, key)
        else:
            return False

        self.dirty[kind_id] = True
        return True

    def get_out_edges(
        self,
        source_id: str,
        target_id: str = "",
        kind_id: str = "",
    ) -> List[Tuple[str, str, str, dict]]:
        """
        Return outgoing edges from a given source node, optionally filtered.

        Parameters:
            source_id: Node from which edges originate.
            target_id: Optional target node filter; if set, only edges to this
                       target are returned.
            kind_id  : Optional edge kind filter; if set, must exist in `EDGE_KIND`.

        Returns:
            A list of tuples `(source_id, target_id, kind_id, data)` for each
            matching edge, where `data` is the edge attribute dict.

        Raises:
            StoryGraphError: if `kind_id` is non-empty and not a known edge kind.
        """
        if kind_id and kind_id not in self.project.edgekinds:
            raise StoryGraphError(f'invalid edge kind: {kind_id}')

        result: List[Tuple[str, str, str, dict]] = []
        for _, target, kind, data in self.graph.out_edges(source_id, keys=True, data=True):
            if (not target_id or target == target_id) and (not kind_id or kind == kind_id):
                result.append((source_id, target, kind, data))
        return result

    def get_in_edges(
        self,
        target_id: str,
        source_id: str = "",
        kind_id: str = "",
    ) -> List[Tuple[str, str, str, dict]]:
        """
        Return incoming edges to a given target node, optionally filtered.

        Parameters:
            target_id: Node into which edges arrive.
            source_id: Optional source node filter; if set, only edges from this
                       source are returned.
            kind_id  : Optional edge kind filter; if set, must exist in `EDGE_KIND`.

        Returns:
            A list of tuples `(source_id, target_id, kind_id, data)` for each
            matching edge, where `data` is the edge attribute dict.

        Raises:
            StoryGraphError: if `kind_id` is non-empty and not a known edge kind.
        """
        if kind_id and kind_id not in self.project.edgekinds:
            raise StoryGraphError(f'invalid edge kind: {kind_id}')

        result: List[Tuple[str, str, str, dict]] = []
        for source, _, kind, data in self.graph.in_edges(target_id, keys=True, data=True):
            if (not source_id or source == source_id) and (not kind_id or kind == kind_id):
                result.append((source, target_id, kind, data))
        return result



    def nodes(self, kind: str = ''):
        if not kind:
            return self.graph.nodes(data=True)

        if kind not in self.project.nodekinds:
            return {}

        nodes = {}
        for k,d in self.graph.nodes(data=True):
            if d['kind'] == kind:
                nodes[k] = d
        return nodes

    # def model_post_init(self, __context) -> None:
    #     super().model_post_init(__context)



@app.get("/ui/graph/{story_id}", response_model=GraphUi)
def get_ui_graph(story_id: str):
    nodes: list[NodeUi] = []
    for node_id, node in project.graph.graph.nodes(data=True):
        nodes.append(
            NodeUi(
                id=node_id,
                kind=node.get("kind", "node"),
                label=node.get("label", node_id),
                x=node.get("x", 0.0),
                y=node.get("y", 0.0),
                data=node,  # or a filtered dict
            )
        )

    edges: list[EdgeUi] = []
    for u, v, key, data in project.graph.graph.edges(keys=True, data=True):
        edge_id = data.get("id", f'{u} {data.get('kind')}.{key} {v}')
        edges.append(
            EdgeUi(
                id=edge_id,
                kind=data.get("kind", "edge"),
                source=u,
                target=v,
                key=key,
                label=data.get("label", ''),
                weight=data.get("weight", 1.0),
                data=data,  # or filtered
            )
        )
        print(f'{edge_id} {u} {v} {key} {data}')

    return GraphUi(nodes=nodes, edges=edges)



PATH = "A space novella.sqlite"
if os.path.exists(PATH):
    os.remove(PATH)

project: Project = Project(title="A space novella", nodekinds=NODEKINDS, edgekinds=EDGEKINDS, affectdefs=AFFECTDEFS)
project.add_story('a_space_novella', 'A space novella')
project.add_scene('scene1', 'Scene 1')
project.add_scene('scene2', 'Scene 2')
project.graph.add_edge('contains', 'a_space_novella', 'scene1', None, {'role': 'scene', 'position': 1})
project.graph.add_edge('contains', 'a_space_novella', 'scene2', None, {'role': 'scene', 'position': 2})
project.graph.add_edge('follows', 'scene2', 'scene1', None, {'role': 'next'})
project.add_beat('beat1', 'Beat 1')
project.add_beat('beat2', 'Beat 2')
project.graph.add_edge('contains', 'scene1', 'beat1', None, {'role': 'beat', 'position': 1})
project.graph.add_edge('contains', 'scene1', 'beat2', None, {'role': 'beat', 'position': 2})
project.graph.add_edge('follows', 'beat2', 'beat1', None, {'role': 'next'})
project.add_character('mirrhe', 'Mirrhe', 'protagonist', 'About Mirrhe...')


Project.model_rebuild()
