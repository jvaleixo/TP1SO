package fliperama.ufsj.edu.br;
import java.util.ArrayList;
import java.util.List;

import fliperama.ufsj.edu.br.util.Scan;

public class Principal {
	
	private static List<Usuario> usuarios =  new ArrayList<Usuario>();
	private static List<Jogo> jogos =  new ArrayList<Jogo>();
	
	public static void main(String[] args) {
		
		int opcao = 30;
		//primeiro Atendente do systema
		Atendente A = new Atendente();
		A.cadastrarUsuario("admin", "admin");
		usuarios.add(A);
		
		do{	
			System.out.println("\t\tMENU\n\n");
			System.out.println("Sair - 0\n");
			System.out.println("Cadastrar Cliente - 1\n");
			System.out.println("Efetuar Login - 2\n");
			System.out.println("Escolha uma opção: ");
			opcao = Integer.parseInt(Scan.readLine());
			
			 switch ( opcao ) {
		        case 1 :
		        	System.out.println("\nCadastar Cliente\n");
		        	cadastrarUsuario(false);
		        	break;
	            case 2 :
	            	int login = 1;
	            	while(login > 0) {
	            		System.out.println("\nEfetuar Login");
	            		Usuario U = realizarLogin();
	            		if(U != null) 
	            			if(U.getRoot()) {
	            				System.out.println("\n\nMenu Atendente\n\n");
	            			}else {
	            				System.out.println("\n\nMenu Cliente\n\n");
	            			}
	            		else {
	            			System.out.println("\nUsuario ou senha incorretos ou não existente");
	            		}
	            		
	            	}
	            	break;
			 }
			 
		}while(opcao != 0);
	}
	
	public static void cadastrarUsuario(Boolean root) {
		
		System.out.println("Nome de Usuario: ");
	    String nome = Scan.readLine();
	    System.out.println("Senha do Usuario: ");
	    String senha = Scan.readLine();
	    if(root) {
			Atendente atendente = new Atendente();
			if(atendente.cadastrarUsuario(nome, senha)) {
				usuarios.add(atendente);
				System.out.println("\nAtendente Cadastrado\n\n");
			}
		}else {
			Cliente cliente = new Cliente();
			if(cliente.cadastrarUsuario(nome, senha)) {
				usuarios.add(cliente);
				System.out.println("\nCliente Cadastrado\n\n");
			}
		}
	}
	
	public static Usuario realizarLogin() {
		System.out.println("Login: ");
	    String nome = Scan.readLine();
	    System.out.println("Senha: ");
	    String senha = Scan.readLine();
	    
	    for(Usuario usuario : usuarios) {
	    	if(usuario.fazerLogin(nome, senha)){
	    		return usuario;
	    	}
	    }
	    return null;
	}
}
