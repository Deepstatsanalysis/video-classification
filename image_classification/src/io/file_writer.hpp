#pragma once

#include "../forwarddeclarations.hpp"

namespace ic {

    class FileWriter {
        private:
            std::ofstream m_file;
        public:
            FileWriter(std::string fileName);
            void writeLine(std::string text);
            void writeLine(float text);
            void close();
    };

}
