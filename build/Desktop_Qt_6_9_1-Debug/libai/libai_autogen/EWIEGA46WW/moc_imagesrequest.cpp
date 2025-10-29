/****************************************************************************
** Meta object code from reading C++ file 'imagesrequest.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libai/imagesrequest.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagesrequest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN2ai13ImagesRequestE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::ImagesRequest::qt_create_metaobjectdata<qt_meta_tag_ZN2ai13ImagesRequestE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::ImagesRequest",
        "Background",
        "Background_Auto",
        "Background_Transparent",
        "Background_Opaque",
        "Background_Custom",
        "Model",
        "Model_DallE2",
        "Model_DallE3",
        "Model_GptImage1",
        "Model_Custom",
        "Moderation",
        "Moderation_Auto",
        "Moderation_Low",
        "Moderation_Custom",
        "OutputFormat",
        "OutputFormat_Png",
        "OutputFormat_Jpeg",
        "OutputFormat_Webp",
        "OutputFormat_Custom",
        "Quality",
        "Quality_Auto",
        "Quality_Low",
        "Quality_Medium",
        "Quality_High",
        "Quality_Hd",
        "Quality_Standard",
        "Quality_Custom",
        "ResponseFormat",
        "ResponseFormat_Url",
        "ResponseFormat_B64Json",
        "ResponseFormat_Custom",
        "Size",
        "Size_Auto",
        "Size_256x256",
        "Size_512x512",
        "Size_1024x1024",
        "Size_1536x1024",
        "Size_1024x1536",
        "Size_1792x1024",
        "Size_1024x1792",
        "Size_Custom",
        "Style",
        "Style_Vivid",
        "Style_Natural",
        "Style_Custom"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Background'
        QtMocHelpers::EnumData<Background>(1, 1, QMC::EnumFlags{}).add({
            {    2, Background::Background_Auto },
            {    3, Background::Background_Transparent },
            {    4, Background::Background_Opaque },
            {    5, Background::Background_Custom },
        }),
        // enum 'Model'
        QtMocHelpers::EnumData<Model>(6, 6, QMC::EnumFlags{}).add({
            {    7, Model::Model_DallE2 },
            {    8, Model::Model_DallE3 },
            {    9, Model::Model_GptImage1 },
            {   10, Model::Model_Custom },
        }),
        // enum 'Moderation'
        QtMocHelpers::EnumData<Moderation>(11, 11, QMC::EnumFlags{}).add({
            {   12, Moderation::Moderation_Auto },
            {   13, Moderation::Moderation_Low },
            {   14, Moderation::Moderation_Custom },
        }),
        // enum 'OutputFormat'
        QtMocHelpers::EnumData<OutputFormat>(15, 15, QMC::EnumFlags{}).add({
            {   16, OutputFormat::OutputFormat_Png },
            {   17, OutputFormat::OutputFormat_Jpeg },
            {   18, OutputFormat::OutputFormat_Webp },
            {   19, OutputFormat::OutputFormat_Custom },
        }),
        // enum 'Quality'
        QtMocHelpers::EnumData<Quality>(20, 20, QMC::EnumFlags{}).add({
            {   21, Quality::Quality_Auto },
            {   22, Quality::Quality_Low },
            {   23, Quality::Quality_Medium },
            {   24, Quality::Quality_High },
            {   25, Quality::Quality_Hd },
            {   26, Quality::Quality_Standard },
            {   27, Quality::Quality_Custom },
        }),
        // enum 'ResponseFormat'
        QtMocHelpers::EnumData<ResponseFormat>(28, 28, QMC::EnumFlags{}).add({
            {   29, ResponseFormat::ResponseFormat_Url },
            {   30, ResponseFormat::ResponseFormat_B64Json },
            {   31, ResponseFormat::ResponseFormat_Custom },
        }),
        // enum 'Size'
        QtMocHelpers::EnumData<Size>(32, 32, QMC::EnumFlags{}).add({
            {   33, Size::Size_Auto },
            {   34, Size::Size_256x256 },
            {   35, Size::Size_512x512 },
            {   36, Size::Size_1024x1024 },
            {   37, Size::Size_1536x1024 },
            {   38, Size::Size_1024x1536 },
            {   39, Size::Size_1792x1024 },
            {   40, Size::Size_1024x1792 },
            {   41, Size::Size_Custom },
        }),
        // enum 'Style'
        QtMocHelpers::EnumData<Style>(42, 42, QMC::EnumFlags{}).add({
            {   43, Style::Style_Vivid },
            {   44, Style::Style_Natural },
            {   45, Style::Style_Custom },
        }),
    };
    return QtMocHelpers::metaObjectData<ImagesRequest, qt_meta_tag_ZN2ai13ImagesRequestE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::ImagesRequest::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Request>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai13ImagesRequestE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai13ImagesRequestE_t>.data,
    nullptr,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai13ImagesRequestE_t>.metaTypes,
    nullptr
} };

QT_WARNING_POP
