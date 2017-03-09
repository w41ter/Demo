package symbols;

import java.util.*;
import lexer.*;
import inter.*;

public class Env {
	private Hashtable<Token, Id> table;
	protected Env prev;
	public Env(Env n) { table = new Hashtable<Token, Id>(); prev = n; }
	public void put(Token v, Id i) { table.put(v, i); }
	public Id get(Token w) {
		for (Env e = this; e != null; e = e.prev) {
			Id found = (Id)(e.table.get(w));
			if (found != null) 
				return found;
		}
		return null;
	}
}