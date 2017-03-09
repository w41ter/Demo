package inter;

import lexer.*;
import symbols.*;

public class Or extends Logical {
	public Or(Token tok, Exper x1, Exper x2) { super(tok, x1, x2); }
	public void jumping(int t, int f) {
		int label = t != 0 ? t : newlabel();
		exper1.jumping(label, 0);
		exper2.jumping(t, f);
		if (t == 0) 
			emitlabel(label);
	}
}