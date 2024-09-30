
#include "command.h"
#include "../transformations/transformations.h"

using namespace s21;

ICommand::~ICommand() {}

RotateCommand::RotateCommand(Viewer* v_, double x_, double y_, double z_) : v(v_), x(x_), y(y_), z(z_), prev_x(v_->new_data->alpha_x), prev_y(v_->new_data->alpha_y), prev_z(v_->new_data->alpha_z) {
    qDebug() << "RotateCM " << prev_x << " " << prev_y << " " << prev_z << " " << x << " " << y << " " << z;
}

RotateCommand::RotateCommand(const RotateCommand &first, const RotateCommand &last) {
    if (first.v == last.v) {
        prev_x = first.prev_x;
        prev_y = first.prev_y;
        prev_z = first.prev_z;
        x = last.x;
        y = last.y;
        z = last.z;
        qDebug() << "RotateCM FL" << prev_x << " " << prev_y << " " << prev_z << " " << x << " " << y << " " << z;
    } else throw exception();
}

bool RotateCommand::execute() {
    bool res = false;

    if (!(x == prev_x && y == prev_y && z == prev_z)) {
        v->new_data->alpha_x = x;
        v->new_data->alpha_y = y;
        v->new_data->alpha_z = z;
        rotate_figure(v->new_data);
        v->update();
        res = true;
        qDebug() << "executed";
    }

    return res;
}

void RotateCommand::undo() {
    v->new_data->alpha_x = prev_x;
    v->new_data->alpha_y = prev_y;
    v->new_data->alpha_z = prev_z;
    rotate_figure(v->new_data);
    v->update();
}

MoveCommand::MoveCommand(Viewer *v_, double x_, double y_, double z_) : v(v_), x(x_), y(y_), z(z_), prev_x(v_->new_data->trv.move_vector[crd::x]), prev_y(v_->new_data->trv.move_vector[crd::y]), prev_z(v_->new_data->trv.move_vector[crd::z]) {}

MoveCommand::MoveCommand(const MoveCommand &first, const MoveCommand &last) {
    if (first.v == last.v) {
        prev_x = first.prev_x;
        prev_y = first.prev_y;
        prev_z = first.prev_z;
        x = last.x;
        y = last.y;
        z = last.z;
    } else throw exception();
}

bool MoveCommand::execute() {
    bool res = false;

    if (!(x == prev_x && y == prev_y && z == prev_z)) {
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
    v->new_data->trv.move_vector[crd::x] = prev_x;
    v->new_data->trv.move_vector[crd::y] = prev_y;
    v->new_data->trv.move_vector[crd::z] = prev_z;
    move_figure(v->new_data);
    v->update();
}

ScaleCommand::ScaleCommand(Viewer *v_, double s) : v(v_), scale(s), prev_scale(v_->curr_scale) {}

ScaleCommand::ScaleCommand(const ScaleCommand &first, const ScaleCommand &last) {
    if (first.v == last.v) {
        prev_scale = first.prev_scale;
        scale = last.scale;
    } else throw exception();
}

bool ScaleCommand::execute() {
    bool res = false;

    if (scale != prev_scale) {
        v->curr_scale = scale;
        scale_figure(v->new_data, v->curr_scale);
        v->update();
        res = true;
    }

    return res;
}

void ScaleCommand::undo() {
    v->curr_scale = prev_scale;
    scale_figure(v->new_data, v->curr_scale);
    v->update();
}

BgColorCommand::BgColorCommand(Viewer *v_, double r_, double g_, double b_) : v(v_), r(r_), g(g_), b(b_), prev_r(v_->bg_r), prev_g(v_->bg_g), prev_b(v_->bg_b) {}

BgColorCommand::BgColorCommand(const BgColorCommand &first, const BgColorCommand &last) {
    if (first.v == last.v) {
        prev_r = first.prev_r;
        prev_g = first.prev_g;
        prev_b = first.prev_b;
        r = last.r;
        g = last.g;
        b = last.b;
    } else throw exception();
}

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

VertexColorCommand::VertexColorCommand(const VertexColorCommand &first, const VertexColorCommand &last) {
    if (first.v == last.v) {
        prev_r = first.prev_r;
        prev_g = first.prev_g;
        prev_b = first.prev_b;
        r = last.r;
        g = last.g;
        b = last.b;
    } else throw exception();
}

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

PolygonColorCommand::PolygonColorCommand(const PolygonColorCommand &first, const PolygonColorCommand &last) {
    if (first.v == last.v) {
        prev_r = first.prev_r;
        prev_g = first.prev_g;
        prev_b = first.prev_b;
        r = last.r;
        g = last.g;
        b = last.b;
    } else throw exception();
}

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

LineWidthCommand::LineWidthCommand(Viewer *v_, double s) : v(v_), size(s), prev_size(v_->line_width) {}

LineWidthCommand::LineWidthCommand(const LineWidthCommand &first, const LineWidthCommand &last) {
    if (first.v == last.v) {
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

ProjectionTypeCommand::ProjectionTypeCommand(Viewer *v_, int t) : v(v_), type(t), prev_type(v_->projection_type) {}

ProjectionTypeCommand::ProjectionTypeCommand(const ProjectionTypeCommand &first, const ProjectionTypeCommand &last) {
    if (first.v == last.v) {
        prev_type= first.prev_type;
        type = last.type;
    } else throw exception();
}

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

VertexTypeCommand::VertexTypeCommand(Viewer *v_, int t) : v(v_), type(t), prev_type(v_->vertex_type) {}

VertexTypeCommand::VertexTypeCommand(const VertexTypeCommand &first, const VertexTypeCommand &last) {
    if (first.v == last.v) {
        prev_type= first.prev_type;
        type = last.type;
    } else throw exception();
}

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

LineTypeCommand::LineTypeCommand(Viewer *v_, int t) : v(v_), type(t), prev_type(v_->line_type) {}

LineTypeCommand::LineTypeCommand(const LineTypeCommand &first, const LineTypeCommand &last) {
    if (first.v == last.v) {
        prev_type= first.prev_type;
        type = last.type;
    } else throw exception();
}

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

CommandManager *CommandManager::get_CommandManager() {
    static CommandManager cm;
    return &cm;
}

void CommandManager::executeCommand(ICommand *command) {
    if (command->execute()) {
        history.push(command);
        clearUndoHistory();
    }
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
