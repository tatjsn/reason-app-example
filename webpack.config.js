const path = require('path');
const webpack = require('webpack');
const WriteFilePlugin = require('write-file-webpack-plugin');
const config = require('dotenv').config();

module.exports = {
  entry: './lib/js/src/index',
  output: {
    filename: '[name].js',
    path: path.join(__dirname, './public'),
    publicPath: '/public'
  },
  devServer: {
    contentBase: path.resolve(__dirname, 'public')
  },
  plugins: [
    new WriteFilePlugin(),
    new webpack.DefinePlugin({
      'process.env.SPACE_URL': JSON.stringify(process.env.SPACE_URL),
      'process.env.ACCESS_TOKEN': JSON.stringify(process.env.ACCESS_TOKEN)
    })
  ]
};
