import View from "../modules/view"
import Form from "../components/form/form"
import Session from "../models/session"

export default class LoginView extends View {
  constructor(options = {}) {
    super(options);
    this._init();
    this.hide();
  }

  _init() {
    let container = document.querySelector('.content_container');
    this._form = new Form({
      data: {
        fields: [{
            name: 'name',
            placeholder: 'Username',
            class: 'input_text'
          },
          {
            name: 'password',
            placeholder: 'Password',
            type: 'password',
            class: 'input_text'
          }
        ],
        template: 'form/form.tmpl',
        controls: [{
          text: 'Sing in',
          type: 'submit',
          class: 'button1'
        }],

      }
    });
    this._el = this._form._el;
    container.appendChild(this._el);


    window.session = window.session || new Session();
    this._form.on('submit', event => {
      event.preventDefault();
      const formData = this._form.getFormData();
      window.session = new Session();
      console.log("submt", formData)
      window.session.save(formData).then(attrs => {
          window.userinfo = formData;
          this.router.go('/');
        },
        attrs => {
          window.alert("Логин или пароль не верны");
        });
    });


  }



}