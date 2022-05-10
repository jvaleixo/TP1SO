package fliperama.ufsj.edu.br;

import fliperama.ufsj.edu.br.util.Scan;

public class Cliente extends Usuario{
	private int creditos;
	
	public Cliente() {
		super(false);
	}
	//set
	public void setCreditos(int creditos) {
		this.creditos = creditos;
	}
	//get
	public int getCreditos() {
		return this.creditos;
	}
	@Override
	public Boolean cadastrarUsuario(String n, String s) {
		super.setNome(n);
		super.setSenha(s);
		System.out.println("Creditos a ser inseridos: ");
	    String creditos = Scan.readLine();
	    this.setCreditos(Integer.parseInt(creditos));
	    
	    return true;
	}
	public void visualizarCliente(Jogo j) {
		
	}
	public void visualizarPontuacao(Jogo j) {
		
	}
}