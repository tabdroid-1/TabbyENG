#include <Base.h>
#include <Tabby.h>

// #include "ExampleLayer.h"
#include "Sandbox2D.h"

class Sandbox : public Tabby::Application {
public:
    Sandbox(const Tabby::ApplicationSpecification& specification)
        : Tabby::Application(specification)
    {
        // PushLayer(new Sandbox2D());
        PushLayer(new Base());
    }

    ~Sandbox()
    {
    }
};

Tabby::Application* Tabby::CreateApplication(Tabby::ApplicationCommandLineArgs args)
{
    ApplicationSpecification spec;
    spec.Name = "A winfow";
    spec.WorkingDirectory = "";
    spec.CommandLineArgs = args;

    return new Sandbox(spec);
}

#include <Tabby/Core/EntryPoint.h>
