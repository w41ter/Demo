#include <iostream>
#include <cstring>
#include <ctype.h>

using namespace std;

enum InputMode {
	INSERT,
	OVERWRITE,
};

enum ClipboardState {
	BEGIN,
	NOTHING,
};

const int N = 10005;

InputMode mode = InputMode::INSERT;
ClipboardState state = ClipboardState::NOTHING;

int caret_pos = 0, copy_pos = -1, m, total, clipboard_len;
char clipboard[N], input[N], editor[N];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %s", &m, input);

		// init 
		memset(clipboard, 0, sizeof(clipboard));
		memset(editor, 0, sizeof(editor));
		//clipboard[0] = editor[0] = '\0';
		mode = InputMode::INSERT;
		state = ClipboardState::NOTHING;
		caret_pos = clipboard_len = total = 0;
		copy_pos = -1;

		int len = strlen(input);
		for (int i = 0; i < len; ++i) {
			char ch = input[i];
			// printf("total is: %d\tCaret_pos is : %d\tClipboard_le is : %d\n", total, caret_pos, clipboard_len);
			// printf("cur mode is : %s\n", (mode == INSERT) ? "INSERT" : "OVERWRITE");
			// printf("cur clipboard state is : %s   first pos is %d\n", (state == NOTHING) ? "NOTHING" : "BEGIN", copy_pos);
			// printf("Clipboard is :%s\n", clipboard);
			// char tmp = editor[caret_pos];
			// editor[caret_pos] = '\0';
			// printf("%s", editor);
			// putchar('I');
			// editor[caret_pos] = tmp;
			// printf("%s\n", editor + caret_pos);
			// char ch = getchar();
			switch (ch) {
				case 'L': 
				{
					//printf("User input L and caret_pos is %d\n", caret_pos);
					if (caret_pos > 0) caret_pos--;
				}
				break;
				case 'R':
				{
					if (caret_pos < total) caret_pos++;
				}
				break;
				case 'S':
				{
					if (mode == InputMode::OVERWRITE)
						mode = InputMode::INSERT;
					else 
						mode = InputMode::OVERWRITE;
				}
				break;
				case 'D':
				{
					if (state == ClipboardState::BEGIN) {
						state = ClipboardState::NOTHING;
						clipboard_len = 0;
						int begin = 0, end = 0;
						if (copy_pos > caret_pos) {
							begin = caret_pos;
							end = copy_pos;
						} else {
							begin = copy_pos;
							end = caret_pos;
							caret_pos = begin;
						}
						if (begin - end == 0) break;
						int j = 0;
						while (editor[end + j] != '\0') {
							editor[begin + j] = editor[end + j];
							j++;
						}
						editor[begin + j] = '\0';
						total -= end - begin;
					} else {
						if (caret_pos == total) break;
						for (int i = caret_pos; i < total; ++i) {
							editor[i] = editor[i+1];
						}
						total--;
					}
				}
				break;
				case 'B':
				{
					if (caret_pos == 0) break;
					for (int j = caret_pos - 1; j < total; ++j) {
						editor[j] = editor[j+1];
					}
					caret_pos--; 	//	删除完成后光标前移
					total--;
				}
				break;
				case 'C':
				{
					if (state == ClipboardState::NOTHING) {
						state = ClipboardState::BEGIN;
						copy_pos = caret_pos;
					} else {
						state = ClipboardState::NOTHING;
						if (caret_pos == copy_pos) {
							clipboard[0] = '\0';
							clipboard_len = 0;
						} else {
							int begin = 0, end = 0;
							if (copy_pos > caret_pos) {
								begin = caret_pos;
								end = copy_pos;
							} else {
								begin = copy_pos;
								end = caret_pos;
							}
							clipboard_len = end - begin;
							clipboard[end] = '\0';
							for (int j = 0; j < end - begin; ++j) {
								clipboard[j] = editor[begin + j];
							}
						}
					}
				}
				break;
				case 'V':
				{
					//if (state == ClipboardState::NOTHING) break;
					if (mode == InputMode::INSERT && clipboard_len != 0) {
						int copy_len = clipboard_len;
						if (copy_len + total > m) break;
						//copy_len = (copy_len + total >= m) ? m - total : copy_len;
						editor[total+copy_len] = '\0';
						for (int j = total + copy_len - 1; j >= caret_pos + copy_len; j--) {
							editor[j] = editor[j-copy_len];
						}
						for (int j = 0; j < copy_len; j++) {
							editor[caret_pos++] = clipboard[j];
						}
						total += copy_len;
					} else if (mode == InputMode::OVERWRITE && clipboard_len != 0) {
						if (clipboard_len + caret_pos > total) {
							int copy_len = clipboard_len;
							if (copy_len + caret_pos > m) 
								break;

							for (int j = 0; j < clipboard_len; ++j) {
								editor[caret_pos++] = clipboard[j];
							}
							total = caret_pos;
							editor[caret_pos] = '\0';
						} else {
							for (int j = 0; j < clipboard_len; ++j) {
								editor[caret_pos++] = clipboard[j];
							}
						}
					}
				}	
				break;
				default:
				{
					//if (!islower(ch)) break;
					if (state == ClipboardState::BEGIN)
						state = ClipboardState::NOTHING;

					if (mode == InputMode::INSERT) {
						if (total >= m) break;
						editor[total + 1] = '\0';
						for (int j = total++; j > caret_pos; --j) {
							editor[j] = editor[j-1];
						}
						editor[caret_pos++] = ch;
					} else {
						if (total == m) break;
						editor[caret_pos++] = ch;
						if (caret_pos > total) 
							total++;
					}
				}	
				break;
			}
		}
		if (total == 0) 
			printf("NOTHING\n");
		else 
			printf("%s\n", editor);
	}
	return 0;
}