
#include "command.h"
#include "../transformations/transformations.h"

using namespace s21;

ICommand::~ICommand() {}

RotateCommand::RotateCommand(Viewer* v_, double x_, double y_, double z_) : v(v_), x(x_), y(y_), z(z_), prev_x(v_->new_data->alpha_x), prev_y(v_->new_data->alpha_y), prev_z(v_->new_data->alpha_z) {}

void RotateCommand::execute() {
    v->new_data->alpha_x = x;
    v->new_data->alpha_y = y;
    v->new_data->alpha_z = z;
    rotate_figure(v->new_data);
    v->update();
}

void RotateCommand::undo() {
    v->new_data->alpha_x = prev_x;
    v->new_data->alpha_y = prev_y;
    v->new_data->alpha_z = prev_z;
    rotate_figure(v->new_data);
    v->update();
}

MoveCommand::MoveCommand(Viewer *v_, double x_, double y_, double z_) : v(v_), x(x_), y(y_), z(z_), prev_x(v_->new_data->trv.move_vector[crd::x]), prev_y(v_->new_data->trv.move_vector[crd::y]), prev_z(v_->new_data->trv.move_vector[crd::z]) {}

void MoveCommand::execute() {
    v->new_data->trv.move_vector[crd::x] = x;
    v->new_data->trv.move_vector[crd::y] = y;
    v->new_data->trv.move_vector[crd::z] = z;
    move_figure(v->new_data);
    v->update();
}

void MoveCommand::undo() {
    v->new_data->trv.move_vector[crd::x] = prev_x;
    v->new_data->trv.move_vector[crd::y] = prev_y;
    v->new_data->trv.move_vector[crd::z] = prev_z;
    move_figure(v->new_data);
    v->update();
}

ScaleCommand::ScaleCommand(Viewer *v_, double s) : v(v_), scale(s), prev_scale(v_->curr_scale) {}

void ScaleCommand::execute() {
    v->curr_scale = scale;
    scale_figure(v->new_data, v->curr_scale);
    v->update();
}

void ScaleCommand::undo() {
    v->curr_scale = prev_scale;
    scale_figure(v->new_data, v->curr_scale);
    v->update();
}

BgColorCommand::BgColorCommand(Viewer *v_, double r_, double g_, double b_) : v(v_), r(r_), g(g_), b(b_), prev_r(v_->bg_r), prev_g(v_->bg_g), prev_b(v_->bg_b) {}

void BgColorCommand::execute() {
    v->bg_r = r;
    v->bg_g = g;
    v->bg_b = b;
    v->update();
}

void BgColorCommand::undo() {
    v->bg_r = prev_r;
    v->bg_g = prev_g;
    v->bg_b = prev_b;
    v->update();
}

VertexColorCommand::VertexColorCommand(Viewer *v_, double r_, double g_, double b_) : v(v_), r(r_), g(g_), b(b_), prev_r(v_->vertex_r), prev_g(v_->vertex_g), prev_b(v_->vertex_b) {}

void VertexColorCommand::execute() {
    v->vertex_r = r;
    v->vertex_g = g;
    v->vertex_b = b;
    v->update();
}

void VertexColorCommand::undo() {
    v->vertex_r = prev_r;
    v->vertex_g = prev_g;
    v->vertex_b = prev_b;
    v->update();
}

PolygonColorCommand::PolygonColorCommand(Viewer *v_, double r_, double g_, double b_) : v(v_), r(r_), g(g_), b(b_), prev_r(v_->polygon_r), prev_g(v_->polygon_g), prev_b(v_->polygon_b) {}

void PolygonColorCommand::execute() {
    v->polygon_r = r;
    v->polygon_g = g;
    v->polygon_b = b;
    v->update();
}

void PolygonColorCommand::undo() {
    v->polygon_r = prev_r;
    v->polygon_g = prev_g;
    v->polygon_b = prev_b;
    v->update();
}

VertexSizeCommand::VertexSizeCommand(Viewer *v_, double s) : v(v_), size(s), prev_size(v_->vertex_size) {}

void VertexSizeCommand::execute() {
    v->vertex_size = size;
    v->update();
}

void VertexSizeCommand::undo() {
    v->vertex_size = prev_size;
    v->update();
}

LineWidthCommand::LineWidthCommand(Viewer *v_, double s) : v(v_), size(s), prev_size(v_->line_width) {}

void LineWidthCommand::execute() {
    v->line_width = size;
    v->update();
}

void LineWidthCommand::undo() {
    v->line_width = prev_size;
    v->update();
}

ProjectionTypeCommand::ProjectionTypeCommand(Viewer *v_, int t) : v(v_), type(t), prev_type(v_->projection_type) {}

void ProjectionTypeCommand::execute() {
    v->projection_type = type;
    v->update();
}

void ProjectionTypeCommand::undo() {
    v->projection_type = prev_type;
    v->update();
}

VertexTypeCommand::VertexTypeCommand(Viewer *v_, int t) : v(v_), type(t), prev_type(v_->vertex_type) {}

void VertexTypeCommand::execute() {
    v->vertex_type = type;
    v->update();
}

void VertexTypeCommand::undo() {
    v->vertex_type = prev_type;
    v->update();
}

LineTypeCommand::LineTypeCommand(Viewer *v_, int t) : v(v_), type(t), prev_type(v_->line_type) {}

void LineTypeCommand::execute() {
    v->line_type = type;
    v->update();
}

void LineTypeCommand::undo() {
    v->line_type = prev_type;
    v->update();
}

CommandManager *CommandManager::get_CommandManager() {
    static CommandManager cm;
    return &cm;
}

void CommandManager::executeCommand(ICommand *command) {
    command->execute();
    history.push(command);
    clearUndoHistory();
}

void CommandManager::undoCommand() {
    if (!history.empty()) {
        ICommand* command = history.top();
        command->undo();
        history.pop();
        undoHistory.push(command);
    }
}

void CommandManager::redoCommand() {
    if (!undoHistory.empty()) {
        ICommand* command = undoHistory.top();
        command->execute();
        undoHistory.pop();
        history.push(command);
    }
}

void CommandManager::clear() {
    clearHistory();
    clearUndoHistory();
}

CommandManager::CommandManager() {}

void CommandManager::clearHistory() { while (!history.empty()) history.pop(); }

void CommandManager::clearUndoHistory() { while (!undoHistory.empty()) undoHistory.pop(); }
