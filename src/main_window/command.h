#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <stack>

#include "../graphics/graphics.h"

using namespace std;

namespace s21 {

    class ICommand {
    public:
        virtual ~ICommand();
        virtual void execute() = 0;
        virtual void undo() = 0;
    };

    class RotateCommand : public ICommand {
    public:
        RotateCommand(Viewer* v_, double x_, double y_, double z_);
        void execute() override;
        void undo() override;
    private:
        Viewer* v;
        double x, y, z;
        double prev_x, prev_y, prev_z;
    };

    class MoveCommand : public ICommand {
    public:
        MoveCommand(Viewer* v_, double x_, double y_, double z_);
        void execute() override;
        void undo() override;
    private:
        Viewer* v;
        double x, y, z;
        double prev_x, prev_y, prev_z;
    };

    class ScaleCommand : public ICommand {
    public:
        ScaleCommand(Viewer* v_, double s);
        void execute() override;
        void undo() override;
    private:
        Viewer* v;
        double scale;
        double prev_scale;
    };

    class BgColorCommand : public ICommand {
    public:
        BgColorCommand(Viewer* v_, double r_, double g_, double b_);
        void execute() override;
        void undo() override;
    private:
        Viewer* v;
        double r, g, b;
        double prev_r, prev_g, prev_b;
    };

    class VertexColorCommand : public ICommand {
    public:
        VertexColorCommand(Viewer* v_, double r_, double g_, double b_);
        void execute() override;
        void undo() override;
    private:
        Viewer* v;
        double r, g, b;
        double prev_r, prev_g, prev_b;
    };

    class PolygonColorCommand : public ICommand {
    public:
        PolygonColorCommand(Viewer* v_, double r_, double g_, double b_);
        void execute() override;
        void undo() override;
    private:
        Viewer* v;
        double r, g, b;
        double prev_r, prev_g, prev_b;
    };

    class VertexSizeCommand : public ICommand {
    public:
        VertexSizeCommand(Viewer* v_, double s);
        void execute() override;
        void undo() override;
    private:
        Viewer* v;
        double size;
        double prev_size;
    };

    class LineWidthCommand : public ICommand {
    public:
        LineWidthCommand(Viewer* v_, double s);
        void execute() override;
        void undo() override;
    private:
        Viewer* v;
        double size;
        double prev_size;
    };

    class ProjectionTypeCommand : public ICommand {
    public:
        ProjectionTypeCommand(Viewer* v_, int t);
        void execute() override;
        void undo() override;
    private:
        Viewer* v;
        int type;
        int prev_type;
    };

    class VertexTypeCommand : public ICommand {
    public:
        VertexTypeCommand(Viewer* v_, int t);
        void execute() override;
        void undo() override;
    private:
        Viewer* v;
        int type;
        int prev_type;
    };

    class LineTypeCommand : public ICommand {
    public:
        LineTypeCommand(Viewer* v_, int t);
        void execute() override;
        void undo() override;
    private:
        Viewer* v;
        int type;
        int prev_type;
    };

    class CommandManager {
    public:
        CommandManager(const CommandManager&) = delete;
        void operator =(const CommandManager&) = delete;
        static CommandManager* get_CommandManager();

        void executeCommand(ICommand *command);
        void undoCommand();
        void redoCommand();
        void clear();
    private:
        CommandManager();
        void clearHistory();
        void clearUndoHistory();

        stack<ICommand*> history;
        stack<ICommand*> undoHistory;
    };
}

#endif // COMMAND_H
