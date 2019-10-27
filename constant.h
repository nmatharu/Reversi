// Foreground text colors
const string red_bold = "\033[1;31m";
const string yellow_bold = "\033[1;33m";
const string cyan = "\033[0;36m";
const string white_bold = "\033[1;37m";
const string reset_color = "\033[0m";
 
// Characters for the edges of the board-- this doesn't compile with these characters
// as chars for some reason so they're just strings instead
const string tl_corner = "╔";
const string tr_corner = "╗";
const string bl_corner = "╚";
const string br_corner = "╝";
const string vert_bar = "║";
const string horz_bar = "═";
 
// Delay between board displays for more natural user experience
const int DELAY_MILLISECONDS = 1000;