#include <iostream>
#include <string>

auto get_initial_value(bool reverse, int argc) -> int
{
    return reverse ? argc - 1 : 1;
}

auto get_for_statement(bool reverse, int argc, int control_variable) -> bool
{
    return reverse ? control_variable >= 1 : control_variable < argc;
}


auto print_line(int argc,
                char* argv[],
                bool reverse  = false,
                bool new_line = false)
{
    for (int i = get_initial_value(reverse, argc);
         get_for_statement(reverse, argc, i);
         reverse ? --i : ++i) {
        std::cout << argv[i] << (new_line ? "\n" : "");
    }
}


auto main(int argc, char* argv[]) -> int
{
    auto first_option = argv[1];

    auto new_line      = false;
    auto reverse_line  = false;
    auto no_break_line = false;

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-l")) {
            new_line = true;
        } else if (!strcmp(argv[i], "-r")) {
            reverse_line = true;
        } else if (!strcmp(argv[i], "-n")) {
            no_break_line = true;
        }
    }

    if (new_line and no_break_line and reverse_line) {
        std::cout << "Only one of '-l', '-n' switches can be provided at the "
                     "same time with '-r'.";
        return 0;
    }

    if (!(new_line or reverse_line or no_break_line)) {
        std::cout << "At least one of switches '-r', '-n', '-l' is required.";
        return 0;
    }

    if (!strcmp(first_option, "-r")) {
        print_line(argc, argv, reverse_line, new_line);
    } else if (!strcmp(first_option, "-l")) {
        print_line(argc, argv, reverse_line, new_line);
    } else if (!strcmp(first_option, "-n")) {
        print_line(argc, argv, reverse_line, false);
    } else if (reverse_line and (new_line or no_break_line)) {
        print_line(argc, argv, reverse_line, new_line);
    } else {
        std::cout << "Wrong arguments. Provide one of '-r', '-l', '-n' at the "
                     "first place or pairs '-r -n', '-r -l' in any order";
    }

    return 0;
}