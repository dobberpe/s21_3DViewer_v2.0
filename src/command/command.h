#ifndef COMMAND_H
#define COMMAND_H

#include <deque>
#include <stack>
#include <vector>

#include "../graphics/graphics.h"

#define MAX_HISTORY_SIZE 100000

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
  RotateCommand(Viewer* v_, double x_, double y_, double z_, bool ui);
  RotateCommand(const RotateCommand& prev, const RotateCommand& curr);
  bool execute() override;
  void undo() override;
  tuple<double, double, double> get_angle() const;

 private:
  Viewer* v;
  double x, y, z;
  bool undo_ui;
};

class MoveCommand : public ICommand {
 public:
  MoveCommand(Viewer* v_, double x_, double y_, double z_, bool ui);
  MoveCommand(const MoveCommand& prev, const MoveCommand& curr);
  bool execute() override;
  void undo() override;
  tuple<double, double, double> get_shift() const;

 private:
  Viewer* v;
  double x, y, z;
  bool undo_ui;
};

class ScaleCommand : public ICommand {
 public:
  ScaleCommand(Viewer* v_, double s, bool ui);
  ScaleCommand(const ScaleCommand& prev, const ScaleCommand& curr);
  bool execute() override;
  void undo() override;
  double get_scale() const;

 private:
  Viewer* v;
  double scale;
  bool undo_ui;
};

class BgColorCommand : public ICommand {
 public:
  BgColorCommand(Viewer* v_, double r_, double g_, double b_);
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
  VertexSizeCommand(const VertexSizeCommand& first,
                    const VertexSizeCommand& last);
  bool execute() override;
  void undo() override;
  double get_prev() const;

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
  double get_prev() const;

 private:
  Viewer* v;
  double size;
  double prev_size;
};

class ProjectionTypeCommand : public ICommand {
 public:
  ProjectionTypeCommand(Viewer* v_, int t);
  bool execute() override;
  void undo() override;
  int get_type() const;

 private:
  Viewer* v;
  int type;
  int prev_type;
};

class VertexTypeCommand : public ICommand {
 public:
  VertexTypeCommand(Viewer* v_, int t);
  bool execute() override;
  void undo() override;
  int get_type() const;

 private:
  Viewer* v;
  int type;
  int prev_type;
};

class LineTypeCommand : public ICommand {
 public:
  LineTypeCommand(Viewer* v_, int t);
  bool execute() override;
  void undo() override;
  int get_type() const;

 private:
  Viewer* v;
  int type;
  int prev_type;
};

class CommandManager {
 public:
  CommandManager(const CommandManager&) = delete;
  void operator=(const CommandManager&) = delete;
  static CommandManager& instance();

  void addCommand(ICommand* command);
  void executeCommand(ICommand* command);
  void combineCommand(ICommand* command);
  void combinedCommandFinished();
  ICommand* undoCommand();
  ICommand* redoCommand();
  void clear();

 private:
  CommandManager();
  void clearHistory();
  void clearUndoHistory();

  deque<ICommand*> history;
  stack<ICommand*> undoHistory;
  bool combine_stopper = false;
};
}  // namespace s21

#endif  // COMMAND_H
