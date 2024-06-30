Exemplo de projeto para o [JHelper](https://github.com/AlexeyDmitriev/jhelper/)

# Sobre
Este projeto é uma modificação do exemplo disponível em [jhelper-example-project](https://github.com/AlexeyDmitriev/jhelper/) criado por Alexey Dmitriev. Fiz ajustes para utilizar   `std::cin` e `std::cout` da STL na classe principal, substituindo o uso de `ostream` e `istream`. Adicionei uma função para comparar saídas e colorir o terminal conforme os resultados. Caso queira ver exemplos visuais, confira a pasta com as capturas de tela em [ScreenCapture](https://github.com/acassioglauco/my-jhelper-project/tree/main/ScreenCapture).

Ele utiliza JHelper para automatizar a execução e verificação de testes. As configurações personalizadas incluem:

* **Configuração de Entrada/Saída**: Utilizamos `std::cin` e `std::cout` para entrada e saída padrão.
* **Tipos de Testes**: Configurados para suportar testes com número de casos conhecido e desconhecido.
* **Execução dos Testes**: A classe `Task` é responsável pela resolução dos testes com base nos dados fornecidos.
  
As capturas de tela fornecidas demonstram como os resultados devem aparecer quando a configuração está correta e todos os testes são executados com sucesso.

> [!IMPORTANT]
Consulte o arquivo `README.md` na pasta `ScreenCapture` para orientações adicionais e capturas de tela que ilustram como os resultados devem ser exibidos quando a configuração está correta e todos os testes são executados com sucesso.

> [!TIP]
Baixe a extensão: [Competitive Companion](https://chromewebstore.google.com/detail/competitive-companion/cjnmckjndlpiamhfimnnjmnckgghkjbl)
> 
Configure a porta na extensão para **4243**.
