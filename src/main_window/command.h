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
        virtual bool execute() = 0;
        virtual void undo() = 0;
    };

    class RotateCommand : public ICommand {
    public:
        RotateCommand(Viewer* v_, double x_, double y_, double z_);
        RotateCommand(const RotateCommand& prev, const RotateCommand& curr);
        bool execute() override;
        void undo() override;
    private:
        Viewer* v;
        double x, y, z;
    };

    class MoveCommand : public ICommand {
    public:
        MoveCommand(Viewer* v_, double x_, double y_, double z_);
        MoveCommand(const MoveCommand& first, const MoveCommand& last);
        bool execute() override;
        void undo() override;
    private:
        Viewer* v;
        double x, y, z;
        double prev_x, prev_y, prev_z;
    };

    class ScaleCommand : public ICommand {
    public:
        ScaleCommand(Viewer* v_, double s);
        ScaleCommand(const ScaleCommand& first, const ScaleCommand& last);
        bool execute() override;
        void undo() override;
    private:
        Viewer* v;
        double scale;
        double prev_scale;
    };

    class BgColorCommand : public ICommand {
    public:
        BgColorCommand(Viewer* v_, double r_, double g_, double b_);
        BgColorCommand(const BgColorCommand& first, const BgColorCommand& last);
        bool execute() override;
        void undo() override;
    private:
        Viewer* v;
        double r, g, b;
        double prev_r, prev_g, prev_b;
    };

    class VertexColorCommand : public ICommand {
    public:
        VertexColorCommand(Viewer* v_, double r_, double g_, double b_);
        VertexColorCommand(const VertexColorCommand& first, const VertexColorCommand& last);
        bool execute() override;
        void undo() override;
    private:
        Viewer* v;
        double r, g, b;
        double prev_r, prev_g, prev_b;
    };

    class PolygonColorCommand : public ICommand {
    public:
        PolygonColorCommand(Viewer* v_, double r_, double g_, double b_);
        PolygonColorCommand(const PolygonColorCommand& first, const PolygonColorCommand& last);
        bool execute() override;
        void undo() override;
    private:
        Viewer* v;
        double r, g, b;
        double prev_r, prev_g, prev_b;
    };

    class VertexSizeCommand : public ICommand {
    public:
        VertexSizeCommand(Viewer* v_, double s);
        VertexSizeCommand(const VertexSizeCommand& first, const VertexSizeCommand& last);
        bool execute() override;
        void undo() override;
    private:
        Viewer* v;
        double size;
        double prev_size;
    };

    class LineWidthCommand : public ICommand {
    public:
        LineWidthCommand(Viewer* v_, double s);
        LineWidthCommand(const LineWidthCommand& first, const LineWidthCommand& last);
        bool execute() override;
        void undo() override;
    private:
        Viewer* v;
        double size;
        double prev_size;
    };

    class ProjectionTypeCommand : public ICommand {
    public:
        ProjectionTypeCommand(Viewer* v_, int t);
        ProjectionTypeCommand(const ProjectionTypeCommand& first, const ProjectionTypeCommand& last);
        bool execute() override;
        void undo() override;
    private:
        Viewer* v;
        int type;
        int prev_type;
    };

    class VertexTypeCommand : public ICommand {
    public:
        VertexTypeCommand(Viewer* v_, int t);
        VertexTypeCommand(const VertexTypeCommand& first, const VertexTypeCommand& last);
        bool execute() override;
        void undo() override;
    private:
        Viewer* v;
        int type;
        int prev_type;
    };

    class LineTypeCommand : public ICommand {
    public:
        LineTypeCommand(Viewer* v_, int t);
        LineTypeCommand(const LineTypeCommand& first, const LineTypeCommand& last);
        bool execute() override;
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

        void addCommand(ICommand *command);
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
