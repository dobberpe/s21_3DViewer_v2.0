#include "render_strategy.h"
#include "graphics.h"

void VertexRenderStrategy::render(Viewer *viewer)
{
    if (viewer->vertex_type != NONE)
    {
        if (viewer->vertex_type == ROUND)
            glEnable(GL_POINT_SMOOTH);
        glColor3f(viewer->vertex_r, viewer->vertex_g, viewer->vertex_b);
        glPointSize(viewer->vertex_size);
        auto [vertex_array, amount_vertex] = viewer->w->get_vertex_array();
        glVertexPointer(3, GL_DOUBLE, 0, vertex_array);
        glDrawArrays(GL_POINTS, 0, amount_vertex);
        if (viewer->vertex_type == ROUND)
            glDisable(GL_POINT_SMOOTH);
    }
}

void PolygonRenderStrategy::render(Viewer *viewer)
{
    if (viewer->line_type == DASH_LINE)
    {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 255);
    }
    glLineWidth(viewer->line_width);
    glColor3f(viewer->polygon_r, viewer->polygon_g, viewer->polygon_b);
    auto [polygon_array, polygon_amount] = viewer->w->get_polygon_array();
    for (auto polygon : polygon_array)
        glDrawElements(GL_LINES, polygon.n_points, GL_UNSIGNED_INT,
                       polygon.points.data());
    if (viewer->line_type == DASH_LINE)
        glDisable(GL_LINE_STIPPLE);
}

CompositeRenderStrategy::~CompositeRenderStrategy()
{
    for (RenderStrategy *strategy : strategies)
    {
        delete strategy;
    }
}

void CompositeRenderStrategy::addStrategy(RenderStrategy *strategy)
{
    strategies.push_back(strategy);
}

void CompositeRenderStrategy::render(Viewer *viewer)
{
    for (RenderStrategy *strategy : strategies)
    {
        strategy->render(viewer);
    }
}