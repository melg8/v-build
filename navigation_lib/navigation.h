#ifndef NAVIGATION_H
#define NAVIGATION_H

void ls(const char *path);
void pwd();
void cd(const char *path);
void createdir(const char *path);
void createfile(const char *path);
void removenode(const char *path);
void renamenode(const char *old_name, const char *new_name);
void edit(const char *path);
void viewfile(const char *path);

#endif // NAVIGATION_H
