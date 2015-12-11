package inter;

import lexer.*;
import symbols.*;

public class Not extends Logical {
	public Not(Token tok, Exper x2) { super(tok, x2, x2); }
	public void jumping(int t, int f) { exper2.jumping(f, t); }
	public String toString() { return op.toString() + " " + exper2.toString(); }
}