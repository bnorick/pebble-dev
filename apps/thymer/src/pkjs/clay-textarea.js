'use strict';

module.exports = {
  name: 'textarea',
  template:
    '<div class="component component-textarea">' +
      '<label class="tap-highlight">' +
        '<span class="label">{{{label}}}</span>' +
        '<span class="input">' +
          '<textarea data-manipulator-target {{each key: attributes}}{{key}}="{{this}}"{{/each}}></textarea>' +
        '</span>' +
      '</label>' +
      '{{if description}}<div class="description">{{{description}}}</div>{{/if}}' +
    '</div>',
  style:
    '.section .component-textarea {' +
      'padding: 0;' +
    '}' +
    '.component-textarea label {' +
      'display: block;' +
    '}' +
    '.component-textarea .label {' +
      'display: block;' +
      'padding-bottom: 0.7rem;' +
    '}' +
    '.component-textarea .input {' +
      'display: block;' +
      'margin-top: 0.7rem;' +
      'margin-left: 0;' +
      'width: 100%;' +
      'min-width: 100%;' +
    '}' +
    '.component-textarea textarea {' +
      'display: block;' +
      'width: 100%;' +
      'min-width: 100%;' +
      'max-width: 100%;' +
      'min-height: 16rem;' +
      'margin-left: 0;' +
      'background: #333333;' +
      'border-radius: 0.25rem;' +
      'padding: 0.5rem 0.6rem;' +
      'border: none;' +
      'color: #ffffff;' +
      'font-size: inherit;' +
      'font-family: monospace;' +
      'line-height: 1.4;' +
      '-webkit-appearance: none;' +
      'appearance: none;' +
      'box-sizing: border-box;' +
    '}' +
    '.component-textarea textarea::-webkit-input-placeholder {' +
      'color: #858585;' +
    '}' +
    '.component-textarea textarea::-moz-placeholder {' +
      'color: #858585;' +
    '}' +
    '.component-textarea textarea:-moz-placeholder {' +
      'color: #858585;' +
    '}' +
    '.component-textarea textarea:-ms-input-placeholder {' +
      'color: #858585;' +
    '}',
  manipulator: 'val',
  defaults: {
    label: '',
    description: '',
    attributes: {}
  }
};
