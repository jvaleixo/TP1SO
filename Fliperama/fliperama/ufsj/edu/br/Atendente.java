package fliperama.ufsj.edu.br;

import fliperama.ufsj.edu.br.util.Scan;

public class Atendente extends Usuario{

	public Atendente() {
		super(true);
	}
	
	@Override
	public Boolean cadastrarUsuario(String n, String s) {
		super.setNome(n);
		super.setSenha(s);
	    return true;
	}
	public void cadastrarAtendente(String n, String s) {
		
	}
	public void cadastrarJogo(String n) {
		
	}
	public void definir_pontuação(Cliente C, Jogo j, int p) {
		
	}
	public void visualizarCliente(Cliente C) {
		
	}
	public void buscarCliente(Cliente c) {
		
	}
	public void vusualizarPontuacao(Cliente c, Jogo j) {
		
	}
	public void gereciarCreditos(Cliente c, int cred) {
		
	}
}
