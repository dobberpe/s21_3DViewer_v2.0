#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>

class Viewer;

class RenderStrategy {
 public:
  virtual void render(Viewer* viewer) = 0;
  virtual ~RenderStrategy() {}
};

class VertexRenderStrategy : public RenderStrategy {
 public:
  void render(Viewer* viewer) override;
};

class PolygonRenderStrategy : public RenderStrategy {
 public:
  void render(Viewer* viewer) override;
};

class CompositeRenderStrategy : public RenderStrategy {
 private:
  std::vector<RenderStrategy*> strategies;

 public:
  ~CompositeRenderStrategy();
  void addStrategy(RenderStrategy* strategy);
  void render(Viewer* viewer) override;
};

#endif