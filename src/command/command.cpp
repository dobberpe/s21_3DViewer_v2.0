#include "command.h"
#include "../logger/logger.h"

using namespace s21;

ICommand::~ICommand() {}

RotateCommand::RotateCommand(Viewer* v_, double x_, double y_, double z_, bool ui) : v(v_), x(x_), y(y_), z(z_), undo_ui(ui) {
    Logger::instance().log("created rotate " + QString::number(x) + " " + QString::number(y) + " " + QString::number(z) + " from " + (undo_ui ? "main window" : "viewer"));
}

RotateCommand::RotateCommand(const RotateCommand &prev, const RotateCommand &curr) {
    v = prev.v;
    x = prev.x + curr.x;
    y = prev.y + curr.y;
    z = prev.z + curr.z;
    undo_ui = prev.undo_ui;
    Logger::instance().log("created combined rotate " + QString::number(x) + " " + QString::number(y) + " " + QString::number(z) + " from " + (undo_ui ? "main window" : "viewer"));
}

bool RotateCommand::execute() {
    bool res = false;

    if (x || y || z) {
        v->get_worker()->rotate_figure(x, y, z);
        v->update();
        res = true;
    }

    return res;
}

void RotateCommand::undo() {
    v->get_worker()->rotate_figure(-x, -y, -z);
    v->update();
}

tuple<double, double, double> RotateCommand::get_angle() const { return undo_ui ? make_tuple(x, y, z) : make_tuple(0.0, 0.0, 0.0); }

MoveCommand::MoveCommand(Viewer *v_, double x_, double y_, double z_, bool ui) : v(v_), x(x_), y(y_), z(z_), undo_ui(ui) {
    Logger::instance().log("created move " + QString::number(x) + " " + QString::number(y) + " " + QString::number(z) + " from " + (undo_ui ? "main window" : "viewer"));
}

MoveCommand::MoveCommand(const MoveCommand &prev, const MoveCommand &curr) {
    v = prev.v;
    x = prev.x + curr.x;
    y = prev.y + curr.y;
    z = prev.z + curr.z;
    undo_ui = prev.undo_ui;
    Logger::instance().log("created combined move " + QString::number(x) + " " + QString::number(y) + " " + QString::number(z) + " from " + (undo_ui ? "main window" : "viewer"));
}

bool MoveCommand::execute() {
    bool res = false;

    if (x || y || z) {
        v->get_worker()->move_figure(x, y, z);
        v->update();
        res = true;
    }

    return res;
}

void MoveCommand::undo() {
    v->get_worker()->move_figure(-x, -y, -z);
    v->update();
}

tuple<double, double, double> MoveCommand::get_shift() const { return undo_ui ? make_tuple(x, y, z) : make_tuple(0.0, 0.0, 0.0); }

ScaleCommand::ScaleCommand(Viewer *v_, double s, bool ui) : v(v_), scale(s), undo_ui(ui) {
    Logger::instance().log("created scale " + QString::number(scale) + " from " + (undo_ui ? "main window" : "viewer"));
}

ScaleCommand::ScaleCommand(const ScaleCommand &prev, const ScaleCommand &curr) {
    v = prev.v;
    scale = prev.scale + curr.scale;
    undo_ui = prev.undo_ui;
    Logger::instance().log("created combined scale " + QString::number(scale) + " from " + (undo_ui ? "main window" : "viewer"));
}

bool ScaleCommand::execute() {
    bool res = false;

    if (scale != 0) {
        v->get_worker()->scale(pow(1.001, scale));
        v->update();
        res = true;
    }

    return res;
}

void ScaleCommand::undo() {
    v->get_worker()->scale(pow(1.001, -scale));
    v->update();
}

double ScaleCommand::get_scale() const { return undo_ui ? scale : 0; }

BgColorCommand::BgColorCommand(Viewer *v_, double r_, double g_, double b_) : v(v_), r(r_), g(g_), b(b_), prev_r(v_->bg_r), prev_g(v_->bg_g), prev_b(v_->bg_b) {
    Logger::instance().log("created bgColor " + QString::number(r) + " " + QString::number(g) + " " + QString::number(b));
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

VertexColorCommand::VertexColorCommand(Viewer *v_, double r_, double g_, double b_) : v(v_), r(r_), g(g_), b(b_), prev_r(v_->vertex_r), prev_g(v_->vertex_g), prev_b(v_->vertex_b) {
    Logger::instance().log("created vertexColor " + QString::number(r) + " " + QString::number(g) + " " + QString::number(b));
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

PolygonColorCommand::PolygonColorCommand(Viewer *v_, double r_, double g_, double b_) : v(v_), r(r_), g(g_), b(b_), prev_r(v_->polygon_r), prev_g(v_->polygon_g), prev_b(v_->polygon_b) {
    Logger::instance().log("created polygonColor " + QString::number(r) + " " + QString::number(g) + " " + QString::number(b));
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

VertexSizeCommand::VertexSizeCommand(Viewer *v_, double s) : v(v_), size(s), prev_size(v_->vertex_size) {
    Logger::instance().log("created vertexSize " + QString::number(size));
}

VertexSizeCommand::VertexSizeCommand(const VertexSizeCommand &first, const VertexSizeCommand &last) {
    if (first.v == last.v) {
        v = first.v;
        prev_size = first.prev_size;
        size = last.size;
    } else throw exception();
    Logger::instance().log("created combined vertexSize " + QString::number(size));
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

LineWidthCommand::LineWidthCommand(Viewer *v_, double s) : v(v_), size(s), prev_size(v_->line_width) {
    Logger::instance().log("created lineWidth " + QString::number(size));
}

LineWidthCommand::LineWidthCommand(const LineWidthCommand &first, const LineWidthCommand &last) {
    if (first.v == last.v) {
        v = first.v;
        prev_size = first.prev_size;
        size = last.size;
    } else throw exception();
    Logger::instance().log("created combined lineWidth " + QString::number(size));
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

ProjectionTypeCommand::ProjectionTypeCommand(Viewer *v_, int t) : v(v_), type(t), prev_type(v_->projection_type) {
    Logger::instance().log("created projType " + QString::number(type));
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

int ProjectionTypeCommand::get_type() const { return prev_type; }

VertexTypeCommand::VertexTypeCommand(Viewer *v_, int t) : v(v_), type(t), prev_type(v_->vertex_type) {
    Logger::instance().log("created vertexType " + QString::number(type));
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

int VertexTypeCommand::get_type() const { return prev_type; }

LineTypeCommand::LineTypeCommand(Viewer *v_, int t) : v(v_), type(t), prev_type(v_->line_type) {
    Logger::instance().log("created lineType " + QString::number(type));
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

int LineTypeCommand::get_type() const { return prev_type; }

CommandManager &CommandManager::instance() {
    static CommandManager cm;
    return cm;
}

void CommandManager::addCommand(ICommand *command) {
    Logger::instance().log("add command");
    history.push(command);
    clearUndoHistory();
}

void CommandManager::executeCommand(ICommand *command) {
    Logger::instance().log("exec command");
    if (command->execute()) addCommand(command);
}



void CommandManager::combineCommand(ICommand *command) {
    Logger::instance().log("combine command");

    if (combine_stopper || history.empty()) executeCommand(command);
    else {
        ICommand* prev_command = history.top();
        ICommand* combined_command = nullptr;
        if (dynamic_cast<RotateCommand*>(command) && dynamic_cast<RotateCommand*>(prev_command))
            combined_command = new RotateCommand(*(dynamic_cast<RotateCommand*>(prev_command)), *(dynamic_cast<RotateCommand*>(command)));
        else if (dynamic_cast<MoveCommand*>(command) && dynamic_cast<MoveCommand*>(prev_command))
            combined_command = new MoveCommand(*(dynamic_cast<MoveCommand*>(prev_command)), *(dynamic_cast<MoveCommand*>(command)));
        else if (dynamic_cast<ScaleCommand*>(command) && dynamic_cast<ScaleCommand*>(prev_command))
            combined_command = new ScaleCommand(*(dynamic_cast<ScaleCommand*>(prev_command)), *(dynamic_cast<ScaleCommand*>(command)));
        else if (dynamic_cast<VertexSizeCommand*>(command) && dynamic_cast<VertexSizeCommand*>(prev_command))
            combined_command = new VertexSizeCommand(*(dynamic_cast<VertexSizeCommand*>(prev_command)), *(dynamic_cast<VertexSizeCommand*>(command)));
        else if (dynamic_cast<LineWidthCommand*>(command) && dynamic_cast<LineWidthCommand*>(prev_command))
            combined_command = new LineWidthCommand(*(dynamic_cast<LineWidthCommand*>(prev_command)), *(dynamic_cast<LineWidthCommand*>(command)));
        else executeCommand(command);

        if (combined_command) {
            command->execute();
            history.pop();
            addCommand(combined_command);
            delete prev_command;
            delete command;
        }
    }

    combine_stopper = false;

    Logger::instance().log("history size " + QString::number(history.size()));
}

void CommandManager::combinedCommandFinished() { combine_stopper = true; }

ICommand *CommandManager::undoCommand() {
    Logger::instance().log("undo command");
    ICommand *command = nullptr;

    if (!history.empty()) {
        Logger::instance().log("undoing");
        command = history.top();
        command->undo();
        history.pop();
        undoHistory.push(command);
    } else Logger::instance().log("nothing to undo");

    return command;
}

ICommand *CommandManager::redoCommand() {
    Logger::instance().log("redo command");
    ICommand *command = nullptr;

    if (!undoHistory.empty()) {
        Logger::instance().log("redoing");
        command = undoHistory.top();
        command->execute();
        undoHistory.pop();
        history.push(command);
    } else Logger::instance().log("nothing to redo");

    return command;
}

void CommandManager::clear() {
    clearHistory();
    clearUndoHistory();
}

CommandManager::CommandManager() {}

void CommandManager::clearHistory() {
    Logger::instance().log("clear undo");
    while (!history.empty()) {
        delete history.top();
        history.pop();
    }
}

void CommandManager::clearUndoHistory() {
    Logger::instance().log("clear redo");
    while (!undoHistory.empty()) {
        delete undoHistory.top();
        undoHistory.pop();
    }
}
