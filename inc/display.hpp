


void drawImage ( sf::RenderWindow *win, Matrix <float> img ) {
    sf::RectangleShape pixel;
    pixel.setSize( sf::Vector2f(10, 10) );

    for ( int i = 0; i < img.getSize().first; ++i ) {
        for ( int j = 0; j < img.getSize().second; ++j ) {

            pixel.setFillColor ( sf::Color( img[j][i], img[j][i], img[j][i] ) );
            pixel.setPosition( 10 + 10 * i, 10 + 10 * j );
            win->draw( pixel );
        }
    }
}

void drawText ( sf::RenderWindow *win, int pos_x, int pos_y, string displayText ) {
    sf::Font font;
    font.loadFromFile( "theboldfont.ttf" );

    sf::Text text;
    text.setFont( font );
    text.setString( displayText );
    text.setPosition ( pos_x, pos_y );

    win->draw( text );
}