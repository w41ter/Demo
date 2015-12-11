package inter;

import symbols.*;

public class Else extends Stmt {
	Exper exper;
	Stmt stmt1, stmt2;
	public Else(Exper x, Stmt s1, Stmt s2) {
		exper  = x;
		stmt1 = s1; 
		stmt2 = s2;
		if (exper.type != Type.Bool)
			exper.error("boolean required in if");
	}
	public void gen(int b, int a) {
		int label1 = newlabel();
		int label2 = newlabel();
		exper.jumping(0, label2);
		emitlabel(label1);
		stmt1.gen(label1, a);
		emit("goto L" + a);
		emitlabel(label2);
		stmt2.gen(label2, a);
	}
}