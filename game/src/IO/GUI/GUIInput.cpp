#include "GUIInput.h"
#include "../../utilities/settings.h"

#include "../../messages/textMessage.h"

void GUIInput::setControls()
{
    try
    {
        controls = controlReader()();
        return;
    }
    catch (std::invalid_argument &e)
    {
        Handle(textMessage(e.what(), textColor::red, textPosition::log).clone());
    }
    catch (nlohmann::json_abi_v3_11_3::detail::parse_error &e)
    {
        Handle(textMessage("Error: Bad json structure in controls!", textColor::red, textPosition::log).clone());
    }
    catch (nlohmann::json_abi_v3_11_3::detail::type_error &e)
    {
        Handle(textMessage("Error: Bad json structure in controls!", textColor::red, textPosition::log).clone());
    }
    catch (std::runtime_error &e)
    {
        Handle(textMessage(e.what(), textColor::red, textPosition::log).clone());
    }
    controls = controlReader().getDefaultControls();
    Handle(textMessage("Default controls initialized!", textColor::red, textPosition::log).clone());
}

void GUIInput::update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Handle(keyMessage(Key::quit).clone());
            break;
        case SDL_KEYDOWN:
            std::string key_name = SDL_GetKeyName(event.key.keysym.sym);
            if (controls.contains(key_name))
            {
                Handle(keyMessage(controls[key_name]).clone());
            }
        }
    }
}

void GUIInput::Handle(std::unique_ptr<Message> message)
{
    handler->Handle(std::move(message));
}

void GUIInput::setNext(messageHandler *handler)
{
    this->handler = handler;
}