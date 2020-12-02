#include <iostream>
#include <string>
#include <vector>

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

auto make_args(int argc, char* argv[]) -> std::vector<std::string>
{
    auto args = std::vector<std::string>{};
    std::copy_n(argv, argc, std::back_inserter(args));
    std::cout << &args << std::endl;
    return args;
}


auto main(int argc, char* argv[]) -> int
{
    auto args = make_args(argc - 1, argv + 1);

    auto first_option = std::string{argv[1]};

    auto new_line      = false;
    auto reverse_order = false;
    auto no_break_line = false;

    //    for (int i = 1; i < argc; ++i) {
    //        if (!strcmp(argv[i], "-l")) {
    //            new_line = true;
    //        } else if (!strcmp(argv[i], "-r")) {
    //            reverse_order = true;
    //        } else if (!strcmp(argv[i], "-n")) {
    //            no_break_line = true;
    //        }
    //    }
    auto operands_start_at = size_t{0};
    //    auto operators_index = int{};
    std::cout << "Argument number: " << args.size() << std::endl;

    for (; operands_start_at < args.size(); ++operands_start_at) {
        auto const& argument = args.at(operands_start_at);
        if (argument == "-r") {
            reverse_order = true;
        } else if (argument == "-l") {
            new_line = true;
        } else if (argument == "-n") {
            no_break_line = true;
        } else if (argument == "--") {
            ++operands_start_at;
            //            operators_index = operands_start_at;
            break;
        } else if (argument.find("-") == 0) {
            std::cerr << "error: unknown option: " << argument << "\n";
            return 1;
        } else {
            std::cout << "No more options" << std::endl;
            break;
        }
    }

    ////    std::cout << "O tutaj: "<< args.begin() << std::endl;
    //    std::vector<std::string> args_to_print;
    ////    std::copy_n(argv, argv[operands_start_at], args_to_print);
    //
    //    std::cout << args_to_print.size() << std::endl;
    ////    std::cout << std::string{args}<< std::endl;
    //    printf(args);
    //
    //    if (new_line and no_break_line and reverse_order) {
    //        std::cout << "Only one of '-l', '-n' switches can be provided at
    //        the "
    //                     "same time with '-r'.";
    //        return 0;
    //    }
    //
    //    if (!(new_line or reverse_order or no_break_line)) {
    //        std::cout << "At least one of switches '-r', '-n', '-l' is
    //        required."; return 0;
    //    }
    //
    //    if (first_option == "-r") {
    //        print_line(argc, argv, reverse_order, new_line);
    //    } else if (first_option == "-l") {
    //        print_line(argc, argv, reverse_order, new_line);
    //    } else if (first_option == "-n") {
    //        print_line(argc, argv, reverse_order, false);
    //    } else if (reverse_order and (new_line or no_break_line)) {
    //        print_line(argc, argv, reverse_order, new_line);
    //    } else {
    //        std::cout << "Wrong arguments. Provide one of '-r', '-l', '-n' at
    //        the "
    //                     "first place or pairs '-r -n', '-r -l' in any order";
    //    }

    return 0;
}