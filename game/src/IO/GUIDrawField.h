#ifndef SEABATTLE_GUIDRAWFIELD_H
#define SEABATTLE_GUIDRAWFIELD_H

class GUIOutput;

class GUIDrawField{
    GUIOutput * output;
    public:
    std::unique_ptr<playFieldMessage> fields[2];
    point2d & pointer;
    GUIDrawField(GUIOutput * output);
    void operator()();
    void setField(std::unique_ptr<playFieldMessage> field);
};

#endif