package inter;

import lexer.*;
import symbols.*;

public class Op extends Exper {
	public Op(Token tok, Type p) { super(tok, p); }
	public Exper reduce() {
		Exper x = gen();
		Temp t = new Temp(type);
		emit(t.toString() + " = " + x.toString());
		return t;
	}
}