package compiler;
import java.io.*;
class Parser
{
	static int lookahead;
	/*Constructor*/
	Parser()throws IOException
	{
		lookahead=System.in.read();
	}

	public void expr()throws IOException
	{
		term();R1();
	}

	public void R1()throws IOException
	{
		while(true)
		{
			if(lookahead=='+')
			{		
				match('+');term();
				System.out.write('+');
				System.out.flush();
			}
			else if(lookahead=='-')	
			{
				match('-');term();
				System.out.write('-');
				System.out.flush();
			}
			break;
		}
	}

	public void term()throws IOException
	{
		factor();R2();	
	}
	
	public void R2()throws IOException
	{
		while(true)
		{
			if(lookahead=='*')
			{
				match('*');factor();
				System.out.write('*');
				System.out.flush();
			}
			else if(lookahead=='/')
			{
				match('/');factor();
				System.out.write('/');
				System.out.flush();
			}
			break;
		}
	}
	public void factor()throws IOException
	{
		if(lookahead=='(')
		{
			match('(');expr();match(')');
		}
		else if(Character.isDigit(lookahead))
		{
			System.out.write(lookahead);
			System.out.flush();
			match(lookahead);
		}
		else throw new Error("sytax error");

	}
	void match(int t)throws IOException
	{
		if(t==lookahead)
		{
			lookahead=System.in.read();
		}
		else
		{
			throw new Error("sytax error!");
		}
	}
}

public class Postfix
{
	public static void main(String[] args)throws IOException
	{
		Parser parser=new Parser();
		parser.expr();
	}
}
