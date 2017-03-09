package inter;

import symbols.*;

public class If extends Stmt {
	Exper exper;
	Stmt stmt;
	public If(Exper x, Stmt s) {
		exper = x;
		stmt = s;
		if (exper.type != Type.Bool) 
			exper.error("boolean required in if");
	}
	public void gen(int b, int a) {
		int label = newlabel();
		exper.jumping(0, a);
		emitlabel(label);
		stmt.gen(label, a);
	}
}