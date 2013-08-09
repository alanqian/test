class FakeInput < SimpleForm::Inputs::Base
  # This method usually returns input's html like <input ... />
  # but in this case it returns just a value of the attribute.
  # <%= f.input :contact_name, :as => :fake, :wrapper => :span, :class =>  %>
  # ref:
  # http://api.rubyonrails.org/classes/ActionView/Helpers/TagHelper.html
  # tag(name, options = nil, open = false, escape = true)
  def input
    @builder.object.send(attribute_name)
  end

  # <%= content_tag :div, :class => "strong" do %> .. <% end %>
  # <%= content_tag :div, @builder.object.field, :class => "strong" %>
end

