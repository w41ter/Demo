package inter;

import symbols.*;

public class While extends Stmt {
	Exper exper;
	Stmt stmt;
	public While() { exper = null; stmt = null; }
	public void init(Exper x, Stmt s) {
		exper = x;
		stmt = s;
		if (exper.type != Type.Bool) 
			exper.error("boolean required in while");
	}
	public void gen(int b, int a) {
		after = a;
		exper.jumping(0, a);
		int label = newlabel();
		emitlabel(label);
		stmt.gen(label, b);
		emit("goto L" + b);
	}
}