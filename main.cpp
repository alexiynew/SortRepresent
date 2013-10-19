#include "Application.h"

int main(int argc, char* argv[]) {

    Application::init(argc, argv);
    Application::run(60);

    return 0;
}
