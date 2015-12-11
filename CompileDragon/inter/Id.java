package inter;

import lexer.*;
import symbols.*;

public class Id extends Exper {
	public int offset;	// 相对地址
	public Id(Word id, Type p, int b) { super(id, p); offset = b; }
}