#pragma once

#include <JuceHeader.h>
#include "SubMarine.h"
#include "Mine.h"
#include "Wall.h"

#include "fmod.hpp"
#include "fmod_studio.hpp"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AnimatedAppComponent, b2ContactListener, b2RayCastCallback
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void update() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
        const b2Vec2& normal, float32 fraction);

private:
    //==============================================================================
    // Your private member variables go here...
    b2World m_World{ {0,10} };

    float m_Angle = 0;
    b2Vec2 m_CamPos{ 0,0 };
    DAE::SubMarine m_SubMarine;
    std::array<DAE::Mine, 2> m_Mines;
    std::array<DAE::Wall, 10> m_Walls;
    juce::Random r{ juce::Time::currentTimeMillis() };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
