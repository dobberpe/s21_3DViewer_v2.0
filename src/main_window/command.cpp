
#include "command.h"
#include "../transformations/transformations.h"

using namespace s21;

ICommand::~ICommand() {}

RotateCommand::RotateCommand(Viewer* v_, double x_, double y_, double z_) : v(v_), x(x_), y(y_), z(z_) {}

RotateCommand::RotateCommand(const RotateCommand &prev, const RotateCommand &curr) {
    v = prev.v;
    x = prev.x + curr.x;
    y = prev.y + curr.y;
    z = prev.z + curr.z;
}

bool RotateCommand::execute() {
    bool res = false;

    if (x || y || z) {
        v->new_data->alpha_x = x;
        v->new_data->alpha_y = y;
        v->new_data->alpha_z = z;
        rotate_figure(v->new_data);
        v->update();
        res = true;
    }

    return res;
}

void RotateCommand::undo() {
    v->new_data->alpha_x = -x;
    v->new_data->alpha_y = -y;
    v->new_data->alpha_z = -z;
    rotate_figure(v->new_data);
    v->update();
}

tuple<double, double, double> RotateCommand::get_angle() const { return make_tuple(x, y, z); }

MoveCommand::MoveCommand(Viewer *v_, double x_, double y_, double z_) : v(v_), x(x_), y(y_), z(z_) {}

MoveCommand::MoveCommand(const MoveCommand &prev, const MoveCommand &curr) {
    v = prev.v;
    x = prev.x + curr.x;
    y = prev.y + curr.y;
    z = prev.z + curr.z;
}

bool MoveCommand::execute() {
    bool res = false;

    if (x || y || z) {
        v->new_data->trv.move_vector[crd::x] = x;
        v->new_data->trv.move_vector[crd::y] = y;
        v->new_data->trv.move_vector[crd::z] = z;
        move_figure(v->new_data);
        v->update();
        res = true;
    }

    return res;
}

void MoveCommand::undo() {
    v->new_data->trv.move_vector[crd::x] = -x;
    v->new_data->trv.move_vector[crd::y] = -y;
    v->new_data->trv.move_vector[crd::z] = -z;
    move_figure(v->new_data);
    v->update();
}

tuple<double, double, double> MoveCommand::get_shift() const { return make_tuple(x, y, z); }

ScaleCommand::ScaleCommand(Viewer *v_, double s) : v(v_), scale(s) {}

ScaleCommand::ScaleCommand(const ScaleCommand &prev, const ScaleCommand &curr) {
    v = prev.v;
    scale = prev.scale + curr.scale;
}

bool ScaleCommand::execute() {
    bool res = false;

    if (scale != 0) {
        v->curr_scale *= pow(scale > 0 ? 1.001 : 0.999, abs(scale));
        scale_figure(v->new_data, v->curr_scale);
        v->update();
        res = true;
    }

    return res;
}

void ScaleCommand::undo() {
    v->curr_scale /= pow(scale > 0 ? 1.001 : 0.999, abs(scale));
    scale_figure(v->new_data, v->curr_scale);
    v->update();
}

double ScaleCommand::get_scale() const { return scale; }

BgColorCommand::BgColorCommand(Viewer *v_, double r_, double g_, double b_) : v(v_), r(r_), g(g_), b(b_), prev_r(v_->bg_r), prev_g(v_->bg_g), prev_b(v_->bg_b) {}

bool BgColorCommand::execute() {
    bool res = false;

    if (!(r == prev_r && g == prev_g && b == prev_b)) {
        v->bg_r = r;
        v->bg_g = g;
        v->bg_b = b;
        v->update();
        res = true;
    }

    return res;
}

void BgColorCommand::undo() {
    v->bg_r = prev_r;
    v->bg_g = prev_g;
    v->bg_b = prev_b;
    v->update();
}

VertexColorCommand::VertexColorCommand(Viewer *v_, double r_, double g_, double b_) : v(v_), r(r_), g(g_), b(b_), prev_r(v_->vertex_r), prev_g(v_->vertex_g), prev_b(v_->vertex_b) {}

bool VertexColorCommand::execute() {
    bool res = false;

    if (!(r == prev_r && g == prev_g && b == prev_b)) {
        v->vertex_r = r;
        v->vertex_g = g;
        v->vertex_b = b;
        v->update();
        res = true;
    }

    return res;
}

void VertexColorCommand::undo() {
    v->vertex_r = prev_r;
    v->vertex_g = prev_g;
    v->vertex_b = prev_b;
    v->update();
}

PolygonColorCommand::PolygonColorCommand(Viewer *v_, double r_, double g_, double b_) : v(v_), r(r_), g(g_), b(b_), prev_r(v_->polygon_r), prev_g(v_->polygon_g), prev_b(v_->polygon_b) {}

bool PolygonColorCommand::execute() {
    bool res = false;

    if (!(r == prev_r && g == prev_g && b == prev_b)) {
        v->polygon_r = r;
        v->polygon_g = g;
        v->polygon_b = b;
        v->update();
        res = true;
    }

    return res;
}

void PolygonColorCommand::undo() {
    v->polygon_r = prev_r;
    v->polygon_g = prev_g;
    v->polygon_b = prev_b;
    v->update();
}

VertexSizeCommand::VertexSizeCommand(Viewer *v_, double s) : v(v_), size(s), prev_size(v_->vertex_size) {}

VertexSizeCommand::VertexSizeCommand(const VertexSizeCommand &first, const VertexSizeCommand &last) {
    if (first.v == last.v) {
        v = first.v;
        prev_size = first.prev_size;
        size = last.size;
    } else throw exception();
}

bool VertexSizeCommand::execute() {
    bool res = false;

    if (size != prev_size) {
        v->vertex_size = size;
        v->update();
        res = true;
    }

    return res;
}

void VertexSizeCommand::undo() {
    v->vertex_size = prev_size;
    v->update();
}

double VertexSizeCommand::get_prev() const { return prev_size; }

LineWidthCommand::LineWidthCommand(Viewer *v_, double s) : v(v_), size(s), prev_size(v_->line_width) {}

LineWidthCommand::LineWidthCommand(const LineWidthCommand &first, const LineWidthCommand &last) {
    if (first.v == last.v) {
        v = first.v;
        prev_size = first.prev_size;
        size = last.size;
    } else throw exception();
}

bool LineWidthCommand::execute() {
    bool res = false;

    if (size != prev_size) {
        v->line_width = size;
        v->update();
        res = true;
    }

    return res;
}

void LineWidthCommand::undo() {
    v->line_width = prev_size;
    v->update();
}

double LineWidthCommand::get_prev() const { return prev_size; }

ProjectionTypeCommand::ProjectionTypeCommand(Viewer *v_, int t) : v(v_), type(t), prev_type(v_->projection_type) {}

bool ProjectionTypeCommand::execute() {
    bool res = false;

    if (type != prev_type) {
        v->projection_type = type;
        v->update();
        res = true;
    }

    return res;
}

void ProjectionTypeCommand::undo() {
    v->projection_type = prev_type;
    v->update();
}

int ProjectionTypeCommand::get_type() const { return prev_type; }

VertexTypeCommand::VertexTypeCommand(Viewer *v_, int t) : v(v_), type(t), prev_type(v_->vertex_type) {}

bool VertexTypeCommand::execute() {
    bool res = false;

    if (type != prev_type) {
        v->vertex_type = type;
        v->update();
        res = true;
    }

    return res;
}

void VertexTypeCommand::undo() {
    v->vertex_type = prev_type;
    v->update();
}

int VertexTypeCommand::get_type() const { return prev_type; }

LineTypeCommand::LineTypeCommand(Viewer *v_, int t) : v(v_), type(t), prev_type(v_->line_type) {}

bool LineTypeCommand::execute() {
    bool res = false;

    if (type != prev_type) {
        v->line_type = type;
        v->update();
        res = true;
    }

    return res;
}

void LineTypeCommand::undo() {
    v->line_type = prev_type;
    v->update();
}

int LineTypeCommand::get_type() const { return prev_type; }

CommandManager *CommandManager::get_CommandManager() {
    static CommandManager cm;
    return &cm;
}

void CommandManager::addCommand(ICommand *command) {
    history.push(command);
    clearUndoHistory();
}

void CommandManager::executeCommand(ICommand *command) {
    if (command->execute()) addCommand(command);
}

ICommand *CommandManager::undoCommand() {
    ICommand *command = nullptr;

    if (!history.empty()) {
        command = history.top();
        command->undo();
        history.pop();
        undoHistory.push(command);
    }

    return command;
}

ICommand *CommandManager::redoCommand() {
    ICommand *command = nullptr;

    if (!undoHistory.empty()) {
        command = undoHistory.top();
        command->execute();
        undoHistory.pop();
        history.push(command);
    }

    return command;
}

void CommandManager::clear() {
    clearHistory();
    clearUndoHistory();
}

CommandManager::CommandManager() {}

void CommandManager::clearHistory() {
    while (!history.empty()) {
        delete history.top();
        history.pop();
    }
}

void CommandManager::clearUndoHistory() {
    while (!undoHistory.empty()) {
        delete undoHistory.top();
        undoHistory.pop();
    }
}
