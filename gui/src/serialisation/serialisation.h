//
// Created by alex on 5/23/19.
//

#ifndef GUI_SERIALISATION_H
#define GUI_SERIALISATION_H

#include <nodes/FlowScene>

#include <QtCore/QJsonObject>

auto serialise(const QtNodes::FlowScene& scene) -> QJsonObject;
void deserialise(QtNodes::FlowScene& scene, const QJsonObject& json);

#endif //GUI_SERIALISATION_H
