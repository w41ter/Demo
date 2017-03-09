package inter;

import lexer.*;
import symbols.*;

public class Unary extends Op {
	public Exper exper;
	public Unary(Token tok, Exper x) {
		super(tok, null);
		exper = x;
		type = Type.max(Type.Int, exper.type);
		if (type == null) 
			error("type error");
	}
	public Exper gen() { return new Unary(op, exper.reduce()); }
	public String toString() { return op.toString() + " " + exper.toString(); }
}