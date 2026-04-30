#pragma once
#include <string>
#include <vector>

struct Project
{
    std::string name;
    std::string imageName;
    std::string description;
    std::string githubLink;
};

class ProjectManager {
public:
    ProjectManager();

    const Project* findProject(const std::string& name) const;
    const std::vector<Project>& getProjects() const;

private:
    std::vector<Project> projects;
};