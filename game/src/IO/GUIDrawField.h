
class GUIOutput;

class GUIDrawField{
    GUIOutput * output;
    playFieldMessage * fields[2];
    point2d & pointer;
    GUIDrawField(GUIOutput * output);
    void operator()();
};