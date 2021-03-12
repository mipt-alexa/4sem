#include <fstream>
#include <string>
#include <vector>
#include <sstream>


void check_in_lit(size_t& curr_pos, std::vector<size_t>& q_positions){
    for (int i = 0; i < q_positions.size(); i+=2) {
        if (curr_pos > q_positions[i] && curr_pos < q_positions[i+1]){
            //std::cout << "position inside the literal!" << std::endl;
            curr_pos = std::string::npos;
        }
    }
}


void find_literals(const std::string& str, std::vector<size_t>& q_pos){
    size_t found_quote, found_sl_quote;
    std::vector<size_t> sl_q_pos;

    found_quote = str.find('\"');
    found_sl_quote = str.find("\\\"");

    while (found_quote != std::string::npos) {
        q_pos.push_back(found_quote);
        found_quote = str.find('\"', found_quote + 1);
    }

    while (found_sl_quote != std::string::npos) {
        sl_q_pos.push_back(found_sl_quote);
        found_sl_quote = str.find("\\\"", found_sl_quote + 1);
    }

    for (const auto x : sl_q_pos) {
        q_pos.erase(std::find(q_pos.cbegin(), q_pos.cend(), x + 1));
    }

}


void erase_single_line_com(std::string& str, std::vector<size_t> quote_pos){
    size_t buf_pos, found_sl = str.find("//");

    while (found_sl != std::string::npos) {
        buf_pos = found_sl;
        check_in_lit(found_sl, quote_pos);

        if (found_sl != std::string::npos) {
            str.erase(found_sl, str.length() - found_sl);
        }

        found_sl = str.find("//", buf_pos + 1);
    }
}


void erase_multi_line_com(std::string& str, std::vector<size_t> quote_pos, bool& comment_now){
    size_t found_sl, found_sl_end;

    found_sl = str.find("/*");
    check_in_lit(found_sl, quote_pos);

    if (found_sl != std::string::npos) {
        found_sl_end = str.find("*/");
        check_in_lit(found_sl_end, quote_pos);

        if (found_sl_end != std::string::npos) {
            str.erase(found_sl, found_sl_end - found_sl + 2);

        } else {
            str.erase(found_sl, str.length());
            comment_now = true;
        }
    }
}


void check_for_com_end(std::string& str, bool& comment_now){
    size_t found_sl_end;
    found_sl_end = str.find("*/");

    if (found_sl_end != std::string::npos){
        str.erase(0, found_sl_end+2);
        comment_now = false;
    }
}


void erase_com_in_string(std::string& buf_str, std::string& result, bool& comment_now){
    std::vector<size_t> quote_pos;

    if (comment_now){
        check_for_com_end(buf_str, comment_now);

    }
    if (!comment_now) {

        find_literals(buf_str, quote_pos);
        erase_single_line_com(buf_str, quote_pos);
        erase_multi_line_com(buf_str, quote_pos, comment_now);

        result += buf_str + '\n';
    }
    quote_pos.clear();

}


int main(){

    std::fstream input_file("../hw6/test1.txt", std::ios::in);

    std::string text((std::istreambuf_iterator<char> (input_file)),
            std::istreambuf_iterator<char> ());


    std::istringstream iss(text);

    std::string buf_str;
    std::string result;

    bool comment_now = false;

    while (std::getline(iss, buf_str, '\n')) {

        if (!buf_str.starts_with("//")) {

            erase_com_in_string(buf_str, result, comment_now);

        }
    }

    std::fstream output_file("../hw6/result1.txt", std::ios::out);

    output_file << result;

    return 0;
}