#include <iostream>
#include <string>


auto print_reverse(int argc, char* argv[])
{
    for (int i = argc - 1; i >= 1; --i) {
        std::cout << argv[i] << " ";
    }
}

auto print_new_line(int argc, char* argv[], bool reverse = false)
{
    if (reverse) {
        for (int i = argc - 1; i >= 1; --i) {
            std::cout << argv[i] << "\n";
        }
    } else {
        for (int i = 1; i < argc; ++i) {
            std::cout << argv[i] << '\n';
        }
    }
}

auto print_no_new_line(int argc, char* argv[], bool reverse = false)
{
    if (reverse) {
        for (int i = argc - 1; i >= 1; --i) {
            std::cout << argv[i] << " ";
        }
    } else {
        for (int i = 1; i < argc; ++i) {
            std::cout << argv[i] << " ";
        }
    }
}


auto main(int argc, char* argv[]) -> int
{
    auto first_option = argv[1];

    auto new_line      = false;
    auto no_break_line = false;
    auto reverse_line  = false;

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-n")) {
            no_break_line = true;
        } else if (!strcmp(argv[i], "-l")) {
            new_line = true;
        } else if (!strcmp(argv[i], "-r")) {
            reverse_line = true;
        }
    }

    if (reverse_line) {
        if (new_line) {
            print_new_line(argc, argv, true);
        } else if (no_break_line) {
            print_no_new_line(argc, argv, true);
        } else {
            print_reverse(argc, argv);
        }
    } else {
        if (!strcmp(first_option, "-n")) {
            print_no_new_line(argc, argv);
        } else if (!strcmp(first_option, "-r")) {
            print_reverse(argc, argv);
        } else if (!strcmp(first_option, "-l")) {
            print_new_line(argc, argv);
        } else {
            print_new_line(argc, argv);
        }
    }


    return 0;
}