#include <vector>
#include <stdio.h>
#include <sstream>
#include <string.h>

//theres so much hacky shit in this to prevent std::string from going out of scope before the corresponding cstr is no longer used
//c++ is a bitch but its much more reusable if this code is contained in a class...
//fuck c++
class Project final {
    public:

        inline void add_file(const char* path) {
            this->files.push_back(path);
        }

        inline void set_output_dir(const char* path) {
            this->build_dir = path;
        }

        inline void set_compiler_flags(const char* flags) {
            this->compiler_flags = flags;
        }

        inline void set_linker_flags(const char* flags) {
            this->linker_flags = flags;
        }

        inline void set_compiler(const char* compiler) {
            this->compiler = compiler;
        }

        inline void build() {
            printf("Beginning build process...\n");
            printf("Compiling %d file(s)...\n", files.size());
            compile();
            printf("Linking...\n");
            link();
            printf("Done!\n");
        }

    private:
        std::vector<const char*> files;
        const char* build_dir = "";
        const char* compiler_flags = "";
        const char* linker_flags = "";
        const char* compiler = "gcc";

        void compile() {
            for (int i = 0; i < files.size(); ++i) {
                const char* file = files[i];
                std::stringstream cmd;
                cmd << this->compiler << " " << file << " " << this->compiler_flags << "-c -o " << build_dir << extract_file(file) << ".o";
                std::string cppstr = cmd.str();
                const char* cmd_str = cppstr.c_str();
                printf(cmd_str);
                printf("\n");
                system(cmd_str);
            }
        }

        void link() {
            std::stringstream cmd;
            cmd << this->compiler << " ";
            for (int i = 0; i < files.size(); ++i) {
                std::stringstream path_buffer;
                path_buffer << build_dir << extract_file(files[i]) << ".o";
                const char* path = strdup(path_buffer.str().c_str());
                cmd << path;
                cmd << " ";
            }
            cmd << this->linker_flags;
            std::string cppstr = cmd.str();
            const char* cmd_str = cppstr.c_str();
            printf(cmd_str);
            printf("\n");
            system(cmd_str);
        }

        const char* extract_file(const char* path) {
            std::stringstream buffer;
            int index = 0;
            while (path[index] != '\0') {
                buffer << path[index];
                if (path[index] == '/')
                    buffer.str("");
                ++index;
            }
            return buffer.str().c_str();
        }


};