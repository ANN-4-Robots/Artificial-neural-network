#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_
int handleEvents( sf::RenderWindow& win ) {
    sf::Event event;
    while ( win.pollEvent( event ) ) {	
        if ( event.type == sf::Event::Closed ) { win.close(); return 1; }
        else if ( event.type == sf::Event::KeyPressed ) {
            switch (event.key.code) {
                case sf::Keyboard::Escape:      win.close(); return 1;
                case sf::Keyboard::Space:       return 2;
                case sf::Keyboard::Return:      return 3;
                default: break;
            }
        }	
    }
    return 0;
}

void drawImage ( sf::RenderWindow &win, Matrix <float> img ) {
    sf::RectangleShape pixel;
    pixel.setSize( sf::Vector2f(10, 10) );

    for ( int i = 0; i < img.getSize().first; ++i ) {
        for ( int j = 0; j < img.getSize().second; ++j ) {

            pixel.setFillColor ( sf::Color( img[j][i], img[j][i], img[j][i] ) );
            pixel.setPosition( 10 + 10 * i, 10 + 10 * j );
            win.draw( pixel );
        }
    }
}

void drawText ( sf::RenderWindow &win, int pos_x, int pos_y, string displayText ) {
    sf::Font font;
    font.loadFromFile( "theboldfont.ttf" );

    sf::Text text;
    text.setFont( font );
    text.setString( displayText );
    text.setPosition ( pos_x, pos_y );

    win.draw( text );
}

void drawOutput ( sf::RenderWindow &win, int pos_x, int pos_y, int size,  Matrix <float> output ) {
    sf::CircleShape circle;
    circle.setRadius( size );
    for (int i = 0; i < output.getSize().second; ++i ) {
        circle.setFillColor ( sf::Color( 255 * output[0][i], 255 * output[0][i], 255 * output[0][i] ) );
        circle.setPosition ( pos_x, pos_y + i * 3 * size );
        win.draw( circle );
        drawText( win, pos_x + 3 * size, pos_y + i * 3 * size, to_string( output[0][i] ) );
        drawText( win, pos_x - 3 * size, pos_y + i * 3 * size, to_string( i ) + " -" );
    }
}

Matrix <float> reshapeMatrix ( Matrix <float> input ) {
    Matrix <float> result(1, input.getSize().first * input.getSize().second );
    for ( int i = 0; i < result.getSize().second; ++i ) {
        result[0][i] = input[i % input.getSize().first][i / input.getSize().first];
    }
    return result;
}


void updateWindow ( sf::RenderWindow& win, Matrix <float> results, Matrix <float> img,
                                            int total, int good, float error, int digit ) {
    win.clear( sf::Color( 51, 51, 51 ) );
    drawImage( win, img );
    drawText( win, 10 , 300, "Current digit: " + to_string( digit ) );
    drawText( win, 10, 400, "Error: " + to_string( error ) );
    drawText( win, 10, 450, "Good: " + to_string( good ) );
    drawText( win, 10, 500, "Total: " + to_string( total ) );
    drawOutput( win, 500, 10, 20, results.T() );
}
// void drawWindow (int good, int total, sf::RenderWindow &win, ) {
//     auto ratio = float(good)/total*100.f;
//     win.clear( sf::Color( 51, 51, 51 ) );
//     drawImage( win, img );
//     drawText( win, 10 , 300, "Current digit: " + to_string( digit ) );
//     drawText( win, 10, 350, "Count: " + to_string( count ) );
//     drawText( win, 10, 400, "Error: " + to_string( nn.getError() ) );
//     drawText( win, 10, 450, "Good: " + to_string( good ) );
//     drawText( win, 10, 500, "Total: " + to_string( total ) );
//     drawText( win, 10, 550, "Ratio: " + to_string( ratio ) + "%" );
//     drawOutput( win, 500, 10, 20, results.T() );
//     win.display();
// }
#endif