package inter;

import symbols.*;

public class Do extends Stmt {
	Exper exper;
	Stmt stmt;
	public Do() { exper = null; stmt = null; }
	public void init(Stmt s, Exper x) {
		exper = x;
		stmt = s;
		if (exper.type != Type.Bool) 
			exper.error("boolean required in do");
	}
	public void gen(int b, int a) {
		after = a;
		int label = newlabel();
		stmt.gen(b, label);
		emitlabel(label);
		exper.jumping(b, 0);
	}
}