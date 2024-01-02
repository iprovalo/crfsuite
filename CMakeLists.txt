cmake_minimum_required(VERSION 3.10)
project(CrfSuite)  # Replace 'MyProject' with your actual project name

# Add subdirectories
add_subdirectory(include)
add_subdirectory(lib/cqdb)
add_subdirectory(lib/crf)
#add_subdirectory(frontend)
#add_subdirectory(swig)

# Documentation and Extra Files
# For simplicity, these are not automatically installed.
# If your project requires installation of docs and extra files, you should add custom commands or targets.

# Example: Install README and other docs
install(FILES README INSTALL COPYING AUTHORS ChangeLog DESTINATION share/doc/MyProject)  # Replace 'MyProject' with your actual package name

# For the example scripts, you might want to copy them to a specific directory,
# or just leave them in the source directory.
