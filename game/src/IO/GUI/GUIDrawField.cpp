#include "GUIDrawField.h"

void GUIDrawField::operator()()
{
    point2d top_indent(0, 60);
    for (auto &field : fields)
    {
        if (field)
        {
            point2d size = field->field->getArea().max_point + point2d(1, 1);
            int field_size = std::max(seabattle::WIDTH / 2, seabattle::HEIGHT / 2) * (seabattle::PLAY_FIELD_SIZE);
            int size_cell = std::min((field_size) / size.x, (field_size) / size.y);
            point2d coordinates;
            switch (field->position)
            {
            case fieldPosition::center:
                coordinates = point2d(seabattle::WIDTH / 2 - field_size / 2, 0) + top_indent;
                break;
            case fieldPosition::left:
                coordinates = point2d(seabattle::WIDTH / 2 - field_size - 10, 0) + top_indent;
                break;
            case fieldPosition::right:
                coordinates = point2d(seabattle::WIDTH / 2 + 10, 0) + top_indent;
            }

            this->drawOutline(coordinates, size, size_cell, field->field_name);
            this->drawField(coordinates, size, size_cell, field->field, field->fog);
            if (field->draw_pointer)
            {
                this->drawPointer(coordinates, size_cell);
            }
        }
    }
}

void GUIDrawField::drawOutline(point2d coordinates, point2d size, int size_cell, std::string field_name)
{
    SDL_Rect field_outline = {.x = coordinates.x - 10, .y = coordinates.y - 10, .w = size.x * size_cell + 20, .h = size.y * size_cell + 20};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &field_outline);
    point2d name_coordinates = point2d(field_outline.w / 2 + field_outline.x, field_outline.h + field_outline.y) + point2d(10, 0);
    textDrawer->drawText(field_name, name_coordinates, {255, 255, 255}, medium, true);
}

void GUIDrawField::drawField(point2d coordinates, point2d size, int size_cell, playField *field, bool fog)
{
    for (int x = 0; x != size.x; x++)
    {
        for (int y = 0; y != size.y; y++)
        {
            SDL_Rect cell_rect = {.x = coordinates.x + x * size_cell, .y = coordinates.y + y * size_cell, .w = size_cell, .h = size_cell};
            SDL_Rect outline = {.x = coordinates.x - 1 + x * size_cell, .y = coordinates.y - 1 + y * size_cell, .w = size_cell + 2, .h = size_cell + 2};
            SDL_Color color;
            auto cell = field->getCell(x, y);
            switch (cell.state)
            {
            case playField::Cell::unknown:
                if (fog)
                {
                    color = seabattle::CELL_UNKNOWN;
                }
                else
                {
                    if (!cell.segment)
                    {
                        color = seabattle::CELL_EMPTY;
                    }
                    else
                    {
                        switch (cell.segment->state)
                        {
                        case Ship::Segment::normal:
                            color = seabattle::SHIP_SEGMENT_NORMAL;
                            break;
                        case Ship::Segment::damaged:
                            color = seabattle::SHIP_SEGMENT_DAMAGED;
                            break;
                        case Ship::Segment::destroyed:
                            color = seabattle::SHIP_SEGMENT_DESTROYED;
                            break;
                        }
                    }
                }
                break;
            case playField::Cell::empty:
                if (fog)
                {
                    color = seabattle::CELL_EMPTY;
                }
                else
                {
                    color = seabattle::CELL_ATTACKED;
                }
                break;

            case playField::Cell::ship:
                if (cell.segment)
                {
                    switch (cell.segment->state)
                    {
                    case Ship::Segment::normal:
                        color = seabattle::SHIP_SEGMENT_NORMAL;
                        break;
                    case Ship::Segment::damaged:
                        color = seabattle::SHIP_SEGMENT_DAMAGED;
                        break;
                    case Ship::Segment::destroyed:
                        color = seabattle::SHIP_SEGMENT_DESTROYED;
                        break;
                    }
                }
                else
                {
                    color = fog ? seabattle::CELL_UNKNOWN : seabattle::CELL_ATTACKED;
                }
                break;
            }
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &cell_rect);
            SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
            SDL_RenderDrawRect(renderer, &cell_rect);
            SDL_RenderDrawRect(renderer, &outline);
        }
    }
}

void GUIDrawField::drawPointer(point2d coordinates, int size_cell)
{
    SDL_Color color = seabattle::POINTER_COLOR;
    for (int x = pointer->area.min_point.x; x != pointer->area.max_point.x + 1; x++)
    {
        for (int y = pointer->area.min_point.y; y != pointer->area.max_point.y + 1; y++)
        {
            point2d cell_coordinates = (pointer->coordinates + point2d(x, y)) * size_cell;
            SDL_Rect cell = {.x = coordinates.x + cell_coordinates.x, .y = coordinates.y + cell_coordinates.y, .w = size_cell, .h = size_cell};
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

void GUIDrawField::setField(std::unique_ptr<playFieldMessage> field)
{
    if (field->visible)
    {
        switch (field->position)
        {
        case fieldPosition::left:
            fields[0] = std::move(field);
            return;
        case fieldPosition::center:
            fields[0] = std::move(field);
            return;
        case fieldPosition::right:
            fields[1] = std::move(field);
            return;
        }
    }
    else
    {
        fields[0] = nullptr;
        fields[1] = nullptr;
    }
}

void GUIDrawField::setRenderer(SDL_Renderer *renderer)
{
    this->renderer = renderer;
}

void GUIDrawField::setTextDrawer(GUIDrawText *textDrawer)
{
    this->textDrawer = textDrawer;
}

void GUIDrawField::setPointer(std::unique_ptr<pointerMessage> pointer)
{
    this->pointer = std::move(pointer);
}
