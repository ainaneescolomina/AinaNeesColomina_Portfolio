#include "ProjectManager.h"

ProjectManager::ProjectManager()
{
    projects = {
        {
            "Galaga Engine",
            "Custom C++ engine with rendering and systems.",
            "https://github.com/you/engine"
        },
        {
            "Roberto el lagarto",
            "My final group project made in Unity for my Advanced Vocational Training \n I was part of the programming team",
            "https://store.steampowered.com/app/2938610/Roberto_el_Lagarto/"
        },
        {
            "Personal Proj",
            "Web-based dev console using C++ + Emscripten.",
            "https://github.com/you/consoleSystem"
        }
    };
}

const Project* ProjectManager::findProject(const std::string& name) const
{
    for (const auto& p : projects)
    {
        if (p.name == name)
            return &p;
    }
    return nullptr;
}

const std::vector<Project>& ProjectManager::getProjects() const
{
    return projects;
}