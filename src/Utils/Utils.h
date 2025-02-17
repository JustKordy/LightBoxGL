#pragma once
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 900

#define SCREEN_WIDTH_HALF (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT_HALF (SCREEN_HEIGHT / 2)

class Utils
{
public:
   
    static const float& GetDeltaTime(){
        return m_DeltaTime;
    }

    static void SetDeltaTime(float deltaTime){
        m_DeltaTime = deltaTime;
    }

    static const bool& isMouseClicked(){
        return MouseClicked;
    }

    static void SetMouseClicked(const bool& state) {
        MouseClicked = state;
    }

private: 
    static float m_DeltaTime;
    static bool MouseClicked;

};

