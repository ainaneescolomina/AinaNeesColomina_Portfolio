#include "ProjectManager.h"

ProjectManager::ProjectManager()
{
    projects = {
        {
            "engine",
            "Custom C++ engine with rendering and systems.",
            "https://github.com/you/engine"
        },
        {
            "dungeonCrawler",
            "Procedural dungeon crawler with AI and combat.",
            "https://github.com/you/dungeonCrawler"
        },
        {
            "consoleSystem",
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