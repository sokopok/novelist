#include "interfaces.h"

namespace novelist {

void Throwable::initializeErrorMesages()
{
    setErrorMessage(NoError, QStringLiteral("No error"));
    setErrorMessage(NoProjectStoreError, QStringLiteral("No project store error"));
    setErrorMessage(ProjectStoreLoadError, QStringLiteral("Project store load error"));
    setErrorMessage(ProjectStoreSaveError, QStringLiteral("Project store save error"));
    setErrorMessage(UnknownProjectStoreError, QStringLiteral("Unknown project store error"));
}

} // namespace novelist
