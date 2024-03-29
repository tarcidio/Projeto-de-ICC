void login(char *name){
    for(;;){                                            //mantendo a tela de login até a entrada do usuário

        char comando = 0;
        FILE *nick;

        cout << "--------------------------------------------------------------------------------";
        cout << "\nEnvie um comando:\n";
        cout << "1 - Entrar\n";
        cout << "2 - Se registrar\n";
        cout << "3 - Sair";
        cout << "\n--------------------------------------------------------------------------------";

        //sugestão: colocar getch
        comando = getch();                         //escolha do comando
        limparTela();
        //Seria interessante se pudessemos tratar o erro em que o usuário tentar logar quando ainda não há
        //nenhum registro de conta
        if(comando == '1'){                                               //comando "entrar no app"

            char nome[30],senha[30],teste[30];
            int caso = 2;

            nick = fopen("dadosLogin.txt","r");
            if(nick == NULL){
                cout<< "Não há usuários registrados ainda, seja o primeiro a se cadastrar\n\n";
                system("pause");
                system("CLS");
            }
            else{
                cout << "\nDigite seu usuário:\n";

                scanf("%[^\n]s", nome);
                setbuf(stdin, NULL);
                limparTela();

                fgets(teste,30,nick);

                if(!feof(nick)){
                    while( !feof(nick) ){
                        fgets(teste,30,nick);                                              //testando os nomes
                        if(strncmp(teste,nome,strlen(nome)) == 0){
                            caso = 1;
                            break;
                        }
                    }

                    //Todos esses casos poderiam virar uma função
                    if(caso == 1){
                        FILE *pass;
                        char pas[100];

                        strcpy(pas,"senhas/");
                        strcat(pas,nome);
                        strcat(pas,".txt");
                        pass = fopen(pas,"r");

                        cout << "\nDigite sua senha:\n";                                        //caso em que o usuario foi encontrado no arquivo
                        scanf("%[^\n]s", senha);
                        fflush(stdin);

                        limparTela();
                        fgets(teste,30,pass);
                        if(strncmp(teste,senha,strlen(teste)) == 0){                            //inscrição da senha
                            fclose(nick);
                            fclose(pass);
                            limparTela();
                            strcpy(name,nome);
                            return;
                        }

                        cout << "\nSenha Errada! Tente Novamente\n\n";                         //Se a senha estiver errada
                        fclose(nick);
                        fclose(pass);
                    }
                    if(caso == 2){                                                             //caso em que o usuario é inexistente
                        printf("\n Usuario Inexistente, por favor registre-se ou reescreva corretamente.\n\n");
                    }
                }
                else{
                    cout<< "Não há usuários registrados ainda, seja o primeiro a se cadastrar\n\n";
                    system("pause");
                    system("CLS");
                }
            }
        }
        if(comando == '2'){                                                               //Comando de cadastro
            int sair = 0;
            char nome[70], senha[70], pas[100];
            FILE *pass;

            while(sair != 1){
                cout << "\nEscreva seu nome de usuário (use, no máximo, 30 caracteres):\n";
                for(;;){
                    scanf("%[^\n]s", nome);
                    setbuf(stdin, NULL);
                    limparTela();
                    if(strlen(nome)<=30 && strlen(nome)>=3){
                        break;
                    }
                    cout << "\nDigite um nome com menos de 30 ou mais de 2 caracteres\n\n";
                }//Podemos colocar uma função que veriica se o usuario tem menos de 20 caracteres

                cout << "\nQual será sua senha, " << nome <<  "?\n";
                for(;;){
                    scanf("%[^\n]s", senha);
                    setbuf(stdin, NULL);
                    limparTela();
                    if(strlen(senha)<=30 && strlen(senha)>=3){
                        break;
                    }
                    cout << "\nDigite uma senha com menos de 30 ou mais de 2 caracteres\n\n";
                }

                cout << "\nSeu nome é: " << nome;
                cout << "\nSua senha é: " << senha;

                cout << "\n\nGostaria de finalizar ou reiniciar o cadastro?" ;
                cout << "Caso reinicie, esse usuário e essa senha não serão cadastradas\n";
                cout << "1 - Finalizar\n";
                cout << "2 - Reiniciar\n\n";

                //Podeira ter a opção de cancelar o registro
                scanf("%d", &sair);
                fflush(stdin);
                limparTela();
            }
            strcpy(pas,"senhas/");
            strcat(pas,nome);
            strcat(pas,".txt");
            pass = fopen(pas,"w+");
            fprintf(pass,"%s",senha);

            nick = fopen("dadosLogin.txt","a");
            fprintf(nick,"\n%s",nome);

            fclose(nick);
            fclose(pass);
            free(nick);
            free(pass);
        }
        if(comando == '3'){
            exit(1);
        }
        if(comando != '1' && comando != '2' && comando != '3'){
            printf("\nComando Inválido!\n\n");
            system("pause");
            system("CLS");
        }
    }
}
