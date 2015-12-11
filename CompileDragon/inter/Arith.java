package inter;

import lexer.*;
import symbols.*;

public class Arith extends Op {
	public Exper exper1, exper2;
	public Arith(Token tok, Exper x1, Exper x2) {
		super(tok, null);
		exper1 = x1;
		exper2 = x2;
		type = Type.max(exper1.type, exper2.type);
		if (type == null) error("type error");
	}
	public Exper gen() { 
		return new Arith(op, exper1.reduce(), exper2.reduce());
	}
	public String toString() {
		return exper1.toString() + " " + op.toString() + " " + exper2.toString();
	}
}