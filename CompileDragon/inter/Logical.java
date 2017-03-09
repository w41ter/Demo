package inter;

import lexer.*;
import symbols.*;

public class Logical extends Exper {
	public Exper exper1, exper2;
	public Logical(Token tok, Exper x1, Exper x2) { 
		super(tok, null);
		exper1 = x1;
		exper2 = x2;
		type = check(exper1.type, exper2.type);
		if (type == null)
			error("type error");
	}
	public Type check(Type p1, Type p2) {
		if (p1 == Type.Bool && p2 == Type.Bool) 
			return Type.Bool;
		else 
			return null;
	}
	public Exper gen() {
		int f = newlabel(), a = newlabel();
		Temp temp = new Temp(type);
		this.jumping(0, f);
		emit(temp.toString() + " = true");
		emit("goto L" + a);
		emitlabel(f);
		emit(temp.toString() + " = false");
		emitlabel(a);
		return temp;
	}
	public String toString() {
		return exper1.toString() + " " + op.toString() + " " + exper2.toString();
	}
}