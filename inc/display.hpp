
bool handleEvents( sf::RenderWindow& win, int& count ) {
    sf::Event event;
    while ( win.pollEvent( event ) ) {	
        if ( event.type == sf::Event::Closed ) win.close();	
        else if ( event.type == sf::Event::KeyPressed ) {
            switch (event.key.code) {
                case sf::Keyboard::Escape:      win.close(); return true;
                case sf::Keyboard::Space:       ++count; break;
            }
        }	
    }
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